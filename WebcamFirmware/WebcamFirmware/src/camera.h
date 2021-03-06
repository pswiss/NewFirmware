/*
 * camera.h
 *
 * Created: 2/14/2018 9:07:19 PM
 *  Author: Wenjia
 
 camera.h contains
 Camera pin definitions
 Camera TWI parameters
 Camera function and variable declarations
 */ 

/*pin definitions for 
TWD0,TWCk0
Camera data bus
HREF,VSYNC
XCLK,PCLK
RST Camera
*/

#ifndef CAMERA_H_
#define CAMERA_H_

#include <asf.h>
#include <ov2640.h>

/******************************* TWI definition*********************************/
/* TWI board defines. */
#define ID_BOARD_TWI                   ID_TWI0
#define BOARD_TWI                      TWI0
#define BOARD_TWI_IRQn                 TWI0_IRQn

/** TWI0 data pin */
#define PIN_TWI_TWD0                   {PIO_PA3A_TWD0, PIOA, ID_PIOA, \
                                         PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 clock pin */
#define PIN_TWI_TWCK0                  {PIO_PA4A_TWCK0, PIOA, ID_PIOA, \
                                         PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 Data pins definition */
#define TWI0_DATA_GPIO                 PIO_PA3_IDX
#define TWI0_DATA_FLAGS                (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_DATA_MASK                 PIO_PA3
#define TWI0_DATA_PIO                  PIOA
#define TWI0_DATA_ID                   ID_PIOA
#define TWI0_DATA_TYPE                 PIO_PERIPH_A
#define TWI0_DATA_ATTR                 PIO_DEFAULT

/** TWI0 clock pins definition */
#define TWI0_CLK_GPIO                  PIO_PA4_IDX
#define TWI0_CLK_FLAGS                 (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_CLK_MASK                  PIO_PA4
#define TWI0_CLK_PIO                   PIOA
#define TWI0_CLK_ID                    ID_PIOA
#define TWI0_CLK_TYPE                  PIO_PERIPH_A
#define TWI0_CLK_ATTR                  PIO_DEFAULT

/** TWI0 pins */
#define PINS_TWI0                      PIN_TWI_TWD0, PIN_TWI_TWCK0

/** Configure TWI0 pins (for OV2640  communications). */
#define CONF_BOARD_TWI0

/******************************* image sensor definitions*********/

/** Enable OV2640 image sensor. */
#define CONF_BOARD_OV2640_IMAGE_SENSOR

/** HSYNC pin */
#define PIN_OV_HSYNC                   { PIO_PA16, PIOA, ID_PIOA, \
	PIO_INPUT, PIO_PULLUP | \
PIO_IT_RISE_EDGE }

/** VSYNC pin */
#define PIN_OV_VSYNC                   { PIO_PA15, PIOA, ID_PIOA, \
	PIO_INPUT, PIO_PULLUP | \
PIO_IT_RISE_EDGE }

/** OV_VSYNC pin definition */
#define OV_VSYNC_GPIO                  PIO_PA15_IDX
#define OV_VSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define OV_VSYNC_MASK                  PIO_PA15
#define OV_VSYNC_PIO                   PIOA
#define OV_VSYNC_ID                    ID_PIOA
#define OV_VSYNC_TYPE                  PIO_PULLUP

/** OV_HSYNC pin definition */
#define OV_HSYNC_GPIO                  PIO_PA16_IDX
#define OV_HSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define OV_HSYNC_MASK                  PIO_PA16
#define OV_HSYNC_PIO                   PIOA
#define OV_HSYNC_ID                    ID_PIOA
#define OV_HSYNC_TYPE                  PIO_PULLUP

/** OV Data Bus pins */
#define OV_DATA_BUS_D0                 PIO_PA24_IDX
#define OV_DATA_BUS_D1                 PIO_PA25_IDX
#define OV_DATA_BUS_D2                 PIO_PA26_IDX
#define OV_DATA_BUS_D3                 PIO_PA27_IDX
#define OV_DATA_BUS_D4                 PIO_PA28_IDX
#define OV_DATA_BUS_D5                 PIO_PA29_IDX
#define OV_DATA_BUS_D6                 PIO_PA30_IDX
#define OV_DATA_BUS_D7                 PIO_PA31_IDX
#define OV_DATA_BUS_FLAGS              (PIO_INPUT | PIO_PULLUP)
#define OV_DATA_BUS_MASK               (0xFF000000UL)
#define OV_DATA_BUS_PIO                PIOA
#define OV_DATA_BUS_ID                 ID_PIOA
#define OV_DATA_BUS_TYPE               PIO_INPUT
#define OV_DATA_BUS_ATTR               PIO_DEFAULT

// Image sensor VSYNC pin.
#define OV2640_VSYNC_PIO	       OV_VSYNC_PIO
#define OV2640_VSYNC_ID		       OV_VSYNC_ID
#define OV2640_VSYNC_MASK              OV_VSYNC_MASK
#define OV2640_VSYNC_TYPE              OV_VSYNC_TYPE
// Image sensor data pin.
#define OV2640_DATA_BUS_PIO            OV_DATA_BUS_PIO
#define OV2640_DATA_BUS_ID             OV_DATA_BUS_ID

/** OV_RST pin definition */
#define OV_FSIN_GPIO                   PIO_PA20_IDX
#define OV_FSIN_FLAGS                  (PIO_OUTPUT_1 | PIO_DEFAULT)
#define OV_FSIN_MASK                   PIO_PA20
#define OV_FSIN_PIO                    PIOA
#define OV_FSIN_ID                     ID_PIOA
#define OV_FSIN_TYPE                   PIO_OUTPUT_1

/******************************* Parallel Capture definition
 *********************************/
/** Parallel Capture Mode Data Enable1 */
#define PIN_PIODCEN1                   PIO_PA15

/** Parallel Capture Mode Data Enable2 */
#define PIN_PIODCEN2                   PIO_PA16

// XCLK
#define PIN_PCK1                       (PIO_PA17_IDX)
#define PIN_PCK1_FLAGS                 (PIO_PERIPH_B | PIO_DEFAULT)

/** Configure PCK1 pins (for OV2640  communications). */
#define CONF_BOARD_PCK1

//#define PIN_PCK0						(PIO_PA23_IDX)
//#define PIN_PCK0_FLAGS					(PIO_PERIPH_A | PIO_DEFAULT)


/////////////////////////////
//not used pins
//#define PIN_OV_SW_OVT                  { PIO_PC10, PIOC, ID_PIOC, \
//PIO_OUTPUT_1, PIO_DEFAULT} /* OV_VDD */
//#define PIN_OV_RST                     { PIO_PC15, PIOC, ID_PIOC, \
//PIO_OUTPUT_1, PIO_DEFAULT}
//#define PIN_OV_FSIN                    { PIO_PA21, PIOA, ID_PIOA, \
//PIO_OUTPUT_0, PIO_DEFAULT}





void vsync_handler(uint32_t ul_id, uint32_t ul_mask);

void init_vsync_interrupts(void);

void configure_twi(void);

void pio_capture_init(Pio *p_pio, uint32_t ul_id);

uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf, uint32_t ul_size);

void init_camera(void);

void configure_camera(void);

uint8_t start_capture(void);

uint32_t find_image_len(void);

//uint8_t *g_p_uc_cap_dest_buf;
#define IMAGE_BUFFER_SIZE 50000
volatile uint8_t g_p_uc_cap_dest_buf[IMAGE_BUFFER_SIZE];

//uint16_t g_us_cap_rows = IMAGE_HEIGHT;

//uint16_t g_us_cap_line = (IMAGE_WIDTH * 2);

volatile uint16_t g_us_cap_size;

volatile int captured_image_start;
volatile int captured_image_end;


#endif /* CAMERA_H_ */