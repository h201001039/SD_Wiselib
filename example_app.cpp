/*
 * Simple Wiselib Example
 */
#include "/home/mindfuck/wiselib/wiselib.testing/external_interface/pc/pc_os_model.h"
#include "/home/mindfuck/wiselib/wiselib.stable/external_interface/external_interface.h"
//#include "algorithms/routing/tree/tree_routing.h"
#include "/home/mindfuck/SD_Wiselib/sd_filesys_lib.h"

typedef wiselib::PCOsModel Os;

class ExampleApplication
{
   public:
      void init( Os::AppMainParameter& value )
      {
         debug_ = &wiselib::FacetProvider<Os, Os::Debug>::get_facet( value );

         debug_->debug( "Reading BIOS Stuff from SD card!\n" );
		//typedef wiselib::ArduinoOsModel Os;
		wiselib::SdFileSystemLibrary<Os> f;
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
int main()
{
application_main(Os);
return 0;
}
