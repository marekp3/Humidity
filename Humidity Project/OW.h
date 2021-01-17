#include <stdbool.h>

#include <stdint.h>


#define OW_PIN C, 4
#define GLUE(a, b) a##b
#define CLR_(what, p, m) (GLUE(what, p) &= ~(1<<(m)))
#define CLR(what, OW_PIN) CLR_(what, OW_PIN)
#define SET_(what, p, m) (GLUE(what, p) |= (1<<(m)))
#define SET(what, OW_PIN) SET_(what, OW_PIN)
#define GET(OW_PIN) GET_(OW_PIN)
#define GET_(/*PIN*/p, m) ((GLUE(PIN,p)) & (1<<(m)))


void OW_init();
void OW_ResetPulse();
bool OW_WaitForPresencePulse();
bool OW_ReadBit();

uint16_t OW_Read8Bits();

