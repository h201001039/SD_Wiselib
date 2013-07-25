/*
 * Simple Wiselib Example
 */
#include "pc_os_model.h"
#include "pc_wiselib_application.h"
#include "external_interface/external_interface.h"
#include "sd_filesys_lib.h"

typedef wiselib::PCOsModel Os;
typedef typename Os::block_data_t block_data_t;
block_data_t buffer[2005];
class ExampleApplication
{
   public:
      void init( Os::AppMainParameter& value )
      {
		  int i,len;
         debug_ = &wiselib::FacetProvider<Os, Os::Debug>::get_facet( value );

         debug_->debug( "Reading BIOS Stuff from SD card!" );
		//typedef wiselib::ArduinoOsModel Os;
		wiselib::SdFileSystemLibrary<Os> f;
		f.init();
		//wiselib::File<Os> x=f.open("abc.txt");
		//printf("return=%d\n",f.dir_rewind());
		//printf("return=%d\n",f.dir_next());
		wiselib::File<Os> x=f.open("harsh");
		len=x.read(buffer,1000);
		if(len>0)
		{
 debug_->debug("reading %d from the file",len);
	for(i=0;i<len;i++)
     printf("%c",buffer[i]);
     printf("\n");
 }
 else if(len==-2)
 debug_->debug("you are at end of the file");
len=x.read(buffer,10);
		if(len>0)
		{
			
 debug_->debug("reading %d from the file",len);
	for(i=0;i<len;i++)
     printf("%c",buffer[i]);
     printf("\n");
 }
 else if(len==-2)
 debug_->debug("you are at end of the file\n");     
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

