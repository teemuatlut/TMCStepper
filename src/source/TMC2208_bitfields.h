#pragma once
#pragma pack(push, 1)

#include <stdint.h>

namespace TMC2224_n {
	struct IOIN_t {
		constexpr static uint8_t address = 0x06;
		union {
			uint32_t sr;
			struct {
				bool  : 1,
							pdn_uart : 1,
							spread : 1,
							dir : 1,
							enn : 1,
							step : 1,
							ms1 : 1,
							ms2 : 1,
							sel_a : 1;
				uint16_t : 15;
				uint8_t version : 8;
			};
		};
	};
}

#pragma pack(pop)
