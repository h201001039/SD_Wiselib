/*
 * Simple Wiselib Example
 */
#include "/home/mindfuck/wiselib/wiselib.testing/external_interface/pc/pc_os_model.h"
#include "/home/mindfuck/wiselib/wiselib.testing/external_interface/pc/pc_wiselib_application.h"
#include "/home/mindfuck/wiselib/wiselib.stable/external_interface/external_interface.h"
//#include "algorithms/routing/tree/tree_routing.h"
#include "/home/mindfuck/SD_Wiselib/sd_filesys_lib.h"

typedef wiselib::PCOsModel Os;
typedef Os::AppMainParameter app;
typedef typename Os::block_data_t block_data_t;
block_data_t buffer[512];
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
		wiselib::File<Os> x=f.open("abc.txt");
		debug_->debug("%d",x.read(buffer,512));
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

