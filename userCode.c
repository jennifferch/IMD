#include<stdio.h>
#include <stdint.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 

/*==================[typedef]================================================*/


int main(){
    // File Descriptor
   int fd;

   // Buffer to store the data received
   int16_t read_buffer[1]; 

   // Number of bytes read by the read() system call
   int bytes_read = 0; 
   
   int i = 0;

   float t;

   int16_t tcounts;

   float tempScale = 333.87f;
   float tempOffset = 21.0f;
   //--------------------- Wellcome -------------- ----------------------------

   printf(" +------------------------------------+ \n");
   printf(" |     MPU 9250 Read Temperatura      | \n");
   printf(" +------------------------------------+ \n");
   printf(" | Press ctrl+c to terminate          | \n");
   printf(" | or wait for 10 readings at 1s rate | \n");
   printf(" +------------------------------------+ \n\n");

   sleep(1);

   //--------------------- Opening the Serial Port ----------------------------

   fd = open("/dev/i2c_mse", O_RDWR); 	                           
   if(fd < 0){ // Error Checking
      printf("Error! in Opening mpu_9250_char\n\n");
      return errno;
   }else{
      printf("mpu_9250_char Opened Successfully\n\n");
   }

   // printing only the received characters
   for(i=0;i<10;i++){	 
      
      // Read the data

      bytes_read = read(fd,&read_buffer,1); 
      
      if ( bytes_read < 0){
         perror("Failed to read the message from the device.");
         return errno;
      }
      
      // Print magnetometer data

      tcounts = read_buffer[0];
     

      t = ((((float) tcounts)  - tempOffset)/ tempScale) + tempOffset;


     printf ("  Temperatura = %f\n", t);

      sleep(1);
   }
   
   //------------ Close mag_hmc5883l_char -------------------------------------
   close(fd);
   printf("mpu_9250_char closed\n\n");

   return 0;}
