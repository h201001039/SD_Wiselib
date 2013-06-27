/*
 * Simple Wiselib Example
 */
#include "external_interface/external_interface.h"
#include "algorithms/routing/tree/tree_routing.h"
#include "/home/mindfuck/Wiselib_SD/sd_filesys_lib.h"

typedef wiselib::OSMODEL Os;

class ExampleApplication
{
   public:
      void init( Os::AppMainParameter& value )
      {
         debug_ = &wiselib::FacetProvider<Os, Os::Debug>::get_facet( value );

         debug_->debug( "Reading BIOS Stuff from SD card!\n" );
		typedef wiselib::ArduinoOsModel Os;
		wiselib::File<Os> f;
		f.init();
     }
      // --------------------------------------------------------------------
   private:
      Os::Debug::self_pointer_t debug_;
};
// --------------------------------------------------------------------------
wiselib::WiselibApplication<Os, ExampleApplication> example_app;
// --------------------------------------------------------------------------
void application_main( Os::AppMainParameter& value )
{
  example_app.init( value );
}
