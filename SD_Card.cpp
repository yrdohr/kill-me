// https://os.mbed.com/questions/1688/Issue-in-Data-logging-in-SD-Card/





// #include "SD_Card.h"

// #ifdef USE_SD_CARD


// SDBlockDevice sd(PB_5, PB_4, PB_3, PF_3);

// int write_sdcard()
// {
//     printf("Initialise and write to a file\n");
//  int err;
//     // call the SDBlockDevice instance initialisation method.

//     err=sd.init();
//     if ( 0 != err) {
//         printf("Init failed %d\n",err);
//         return -1;
//     }
    
//     FATFileSystem fs("sd", &sd);
//     FILE *fp = fopen("/sd/test.txt","w");
//     if(fp == NULL) {
//         error("Could not open file for write\n");
//         sd.deinit();
//         return -1;
//     } else {
//         //Put some text in the file...
//         fprintf(fp, "Martin Says Hi!\n");
//         //Tidy up here
//         fclose(fp);
//         printf("SD Write done...\n");
//         sd.deinit();
//         return 0;
//     }
    
// }

// int read_sdcard()
// {
//     printf("Initialise and read from a file\n");

//     // call the SDBlockDevice instance initialisation method.
//     if ( 0 != sd.init()) {
//         printf("Init failed \n");
//         return -1;
//     }
    
//     FATFileSystem fs("sd", &sd);
//     FILE *fp = fopen("/sd/test.txt","r");
//     if(fp == NULL) {
//         error("Could not open or find file for read\n");
//         sd.deinit();
//         return -1;
//     } else {
//         //Put some text in the file...
//         char buff[64]; buff[63] = 0;
//         while (!feof(fp)) {
//             fgets(buff, 63, fp);
//             printf("%s\n", buff);
//         }
//         //Tidy up here
//         fclose(fp);
//         printf("SD Write done...\n");
//         sd.deinit();
//         return 0;
//     }
// }
// #endif