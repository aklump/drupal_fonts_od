##Summary
This module allows you to programatically add @font-face fonts to a page "on-demand".  _What's the point?_  If you want to have many fonts available without the overhead of loading them all on each page, you should use this module.  Or if the font changes based on server logic, you should use this module.  Since we can't depend on browser consistency for when the fonts are loaded; why not take control of that ourselves?

Here are some links related to the rationalle behind this module.
<http://www.stevesouders.com/blog/2009/10/13/font-face-and-performance/>
<http://paulirish.com/2009/fighting-the-font-face-fout/>
<http://sixrevisions.com/css/font-face-web-fonts-issues/>

##Rationalle
In our use case, we had a node field that allowed the admins to type in a font name.  Then the node would render in that font.  We used pre_process hooks and `fonts_od_add_font()` based on the node field value to include the  @font-face font.  The admins had hundreds of fonts available to them, and we never knew what they would choose, so the dynamic loading idea birthed this module.


##Installation
1. Download and unzip this module into your modules directory.
1. Goto Administer > Site Building > Modules and enable this module.


##Configuration
2. Place the fonts that you wish to use inside a folder called `fonts` in your theme.  Try to include all four common variants: `.woff`, `.ttf`, `.svg`, `.eot`.  The fonts may also live elsewhere, see `hook_fonts_od_fonts()`.
1. You must invoke `hook_fonts_od_fonts()` to inform this module of the fonts available to Drupal.


##Usage
A given @font-face font is only loaded if you employ `fonts_od_add_font()` sometime during the page load.

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
        $style = fonts_od_add_font('Weekend Font');  
      }
      else {
        $style = fonts_od_add_font('Weekday Font');
      }
      $build[] = array('#markup' => '<div style="' . $style . ';">' . t('This will be displayed in our chosen font based on if this is a weekend or not.') . '</div>');
      return $build;
    }
    ?>


##TypeKit.com Integration
Even though you may only enable one font in a given TypeKit kit, the entire kit is loaded.  It's just the way TypeKit works.  So, keep your kits lean and make more kits with one or two fonts, rather than few with many fonts.    


##API

##Contact
**In the Loft Studios**
Aaron Klump - Developer
PO Box 29294 Bellingham, WA 98228-1294
aim: theloft101
skype: intheloftstudios
<http://www.InTheLoftStudios.com>
