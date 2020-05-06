#pragma once

#include "Pokitto.h"
#include "Constants.h"
#include "Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

namespace Utils {

    static inline bool sfxOver() {

        return ( PS::sfxDataPtr >= PS::sfxEndPtr );

    }
    
    static inline void printffloat(float d) {
        
        int a = static_cast<int>(d);
        int b = static_cast<int>((d * 1000)) % 1000;
        
        printf("%i.%i", a, b);
        
    }
            
    
    // This gets the length of an array at compile time
    template< typename T, size_t N > constexpr size_t ArrayLength(T (&)[N]) {
    	return N;
    }
    
    static inline uint16_t getFrameCount() {
    
        return Pokitto::Core::frameCount;
    
    }
    
    static inline uint16_t getFrameCount(uint16_t mod) {
    
        return (Pokitto::Core::frameCount % mod);
    
    }
    
    static inline bool getFrameCountHalf(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) > (mod /2));
    
    }
    
    static inline bool isFrameCount(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) == 0);
    
    }
    
    static inline bool isFrameCount(uint16_t mod, uint16_t val) {
        
        return ((Pokitto::Core::frameCount % mod) == val);
    
    }
    
    
    static inline void drawDottedColumn(uint8_t x, uint8_t sy, uint8_t ey) {
        
        for (uint32_t y = sy; y <= ey; y = y + 2) {
            
            PD::drawPixel(x, y);

        }
    
    }
    
    static inline void drawDottedRow(uint8_t sx, uint8_t ex, uint8_t y) {
        
        for (uint32_t x = sx; x <= ex; x = x + 2) {
            
            PD::drawPixel(x, y);

        }
    
    }
    
    
    // ----------------------------------------------------------------------------
    //  A better absolute as it uses less memory than the standard one .. 
    //
    template<typename T> T absT(const T & v) {
      
        return (v < 0) ? -v : v;
    
    }
    
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint16_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint16_t value) {
    
        for (uint32_t i = 0; i < size; ++i) {
            buffer[i] = value % 10;
            value /= 10;
        }
    
    }
    
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint32_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint32_t value) {
    
        for(uint8_t i = 0; i < size; ++i) {
            buffer[i] = value % 10;
            value /= 10;
        }
    
    }

}
