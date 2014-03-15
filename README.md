##Summary
This module allows you to programatically add @font-face fonts to a page "on-demand".  _What's the point?_  If you want to have many fonts available without the overhead of loading them all on each page, you should use this module.  Or if the font changes based on server logic, you should use this module.  Since we can't depend on browser consistency for when the fonts are loaded; why not take control of that ourselves?

Here are some links related to the rationalle behind this module.
<http://www.stevesouders.com/blog/2009/10/13/font-face-and-performance/>
<http://paulirish.com/2009/fighting-the-font-face-fout/>
<http://sixrevisions.com/css/font-face-web-fonts-issues/>

##Rationalle
In our use case, we had a node field that allowed the admins to type in a font name.  Then the node would render in that font.  We used pre_process hooks and `fonts_od_include_font()` based on the node field value to include the  @font-face font.  The admins had hundreds of fonts available to them, and we never knew what they would choose, so the dynamic loading idea birthed this module.


##Installation
1. Download and unzip this module into your modules directory.
1. Goto Administer > Site Building > Modules and enable this module.


##Configuration
### With the fontyourface module
1. Enable fonts_od_fontyourface module.
2. Visit this page `admin/appearance/fonts-od` and edit the fonts as needed.
3. Start using the module.

## @font-face Integration
1. Place the font files that you wish to use inside a folder called `fonts` in the default theme.  Try to include all four common variants: `.woff`, `.ttf`, `.svg`, `.eot`.
2. By placing them in the `font` folder of the default theme, they will be automatically detected when you clear the cache.
3. The fonts may also live elsewhere, in which case you need to invoke `hook_fonts_od_fonts()` from your custom module.
4. In css you will apply the fallback fonts to the font family
5. You must also include the font using php on the page you wish to display it.

### Detailed Example
#### Save a new font to your theme
1. The default theme is called: gop3_theme.
2. We have download _Open Sans Condensed_ from <http://www.fontsquirrel.com/fonts/open-sans-condensed> and saved it as `gop3_theme/fonts/open-sans-condensed-fontfacekit`
3. Nested folders are fine as the `fonts` folder is scanned recursively.
3. We have not implemented any hooks from fonts_od.
4. Now we clear the Drupal cache.

#### Declare some DOM element's font-family to use this new font
_NOTE: These examples are using Compass._

4. In a stylesheet we've made the following declaration, compare the difference between a regular inclusion of @font-face compared to the second example, an on-demand inclusion.

        // Open Sans Light is not on-demand, is is loaded on every page
        $font_family_sans_light: "Open Sans Light", Arial, Georgia, sans-serif;
        @include font-face("Open Sans Light", font-files("open-sans/OpenSans-Light-webfont.woff", "open-sans/OpenSans-Light-webfont.ttf", "open-sans/OpenSans-Light-webfont.svg", "open-sans/OpenSans-Light-webfont.eot"));        

5. This is an on-demand font declaration

        // But .slice-title refers to the title ONLY on the front page, so we want to use an on-demand font.
        .slice-title {

          // This font is on-demand, yet we include the above as a fallback
          font-family: "Open Sans Condlight", $font_family_sans_light;
        }        

#### Include the font based on some conditional statement using php.
5. .slice-title only appears on the front page so we have added the following to load only when the front page is loading.  This causes our font to be included "on-demand".  Here is the php

        <?php
        if ($this_is_the_front_page) {
          // Note: you can use the machine name or the font-family css title here
          fonts_od_include_font('Open Sans Condlight');
        }

#### (Optional) Rename the font family using `hook_fonts_od_info_alter`
1. You may want to rename the font family from it's auto-detected name, so you can use something else in your css files; refer to `hook_fonts_od_info_alter()` for this. _Beware that any database overrides will ignore the values here, so you may need to revert_.

        <?php
        /**
         * Implements hook_fonts_od_info_alter(&$info).
         *
         * Alter the information provided by modules about available fonts
         */
        function my_module_fonts_od_info_alter(&$info) {
          $info['OpenSans-CondLight-webfont']['title'] = 'Open Sans Narrow'
        }

##TypeKit.com Integration
Even though you may only enable one font in a given TypeKit kit, the entire kit is loaded.  It's just the way TypeKit works.  So, keep your kits lean and make more kits with one or two fonts, rather than few with many fonts.  

##Usage
A given @font-face font is only loaded if you employ `fonts_od_include_font()` sometime during the page load.

Here is some sample code:

    <?php
    /**
     * An example page
     *
     * @return array
     */
    function example_page() {
      $build = array();
      // Check if today is a saturday or sunday
      if (($dow = date('N')) && ($dow == 6 || $dow == 7)) {
        $style = fonts_od_include_font('Weekend Font');  
      }
      else {
        $style = fonts_od_include_font('Weekday Font');
      }
      $build[] = array('#markup' => '<div style="' . $style . ';">' . t('This will be displayed in our chosen font based on if this is a weekend or not.') . '</div>');
      return $build;
    }
    ?>
  


##Contact
**In the Loft Studios**
Aaron Klump - Developer
PO Box 29294 Bellingham, WA 98228-1294
aim: theloft101
skype: intheloftstudios
<http://www.InTheLoftStudios.com>
