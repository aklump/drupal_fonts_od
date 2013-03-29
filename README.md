##Summary
This module allows you to programatically add @font-face fonts to a page "on-demand".  _What's the point?_  If you want to have many fonts available without the overhead of loading them all on each page, you should use this module.  Or if the font changes based on server logic, you should use this module.

##Requirements


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
        $family = fonts_od_add_font('Weekend Font');  
      }
      else {
        $family = fonts_od_add_font('Weekday Font');
      }
      $build[] = array('#markup' => '<div style="font-family: ' . $family . ';">' . t('This will be displayed in our chosen font based on if this is a weekend or not.') . '</div>');
      return $build;
    }
    ?>
    


##API

##Contact
**In the Loft Studios**
Aaron Klump - Developer
PO Box 29294 Bellingham, WA 98228-1294
aim: theloft101
skype: intheloftstudios
<http://www.InTheLoftStudios.com>
