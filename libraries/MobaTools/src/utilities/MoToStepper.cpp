/*
  MobaTools.h - a library for model railroaders
  Author: fpm, fpm@mnet-mail.de
  Copyright (c) 2020 All right reserved.

  Functions for the stepper part of MobaTools
*/
#define COMPILING_MOTOSTEPPER_CPP

//#define debugTP
//#define debugPrint
#include <utilities/MoToDbg.h>
#include <MobaTools.h>
#define TODO	// ignore 
// Global Data for all instances and classes  --------------------------------
#ifdef debugPrint
     const char *rsC[] = { "INACTIVE", "STOPPED", "STOPPING", "STARTING", "CRUISING", "RAMPACCEL", "RAMPDECEL", "SPEEDDECEL" };    
#endif


//==========================================================================
// --------- Class Stepper ---------------------------------
// Class-specific Variables
outUsed_t MoToStepper::outputsUsed;
byte MoToStepper::_stepperCount = 0;

// global functions / Interrupts

// Functions and ISR's that are completely different between ESP8266 and the other platforms
// This applies to all ISR and to the setSpeedSteps method
#ifdef ESP8266
// ISR and methods specific for ESP8266 ( edge triggerd from Step pulse )
#include "utilities/MoToStepperESP8266.inc"
#else
// ISR and methods for all other controllers
#include "utilities/MoToStepperNo8266.inc"
#endif // esp8266 <-> other

// constructor -------------------------
MoToStepper::MoToStepper(long steps ) {
    // constuctor for stepper Class, initialize data
	#ifdef ESP8266
    MoToStepper::initialize ( steps, A4988 );	// This is the only valid mode
	#else
    MoToStepper::initialize ( steps, HALFSTEP );
	#endif
}

MoToStepper::MoToStepper(long steps, uint8_t mode ) {
    #ifdef ESP8266
    mode = STEPDIR; // THis is the only allowed mode
    #endif
    // constuctor for stepper Class, initialize data
    MoToStepper::initialize ( steps, mode );
}

// private functions ---------------
void MoToStepper::initialize ( long steps360, uint8_t mode ) {
    // create new instance
    MODE_TP1;       // activate debug-pins
    MODE_TP2;
    MODE_TP3;
    MODE_TP4;
    _stepperIx = _stepperCount ;
    stepsRev = steps360;       // number of steps for full rotation in fullstep mode
    if ( mode != FULLSTEP && mode != A4988 ) mode = HALFSTEP;
    stepMode = mode;
    // initialize data for interrupts
    _stepperData.stepCnt = 0;         // don't move
    _stepperData.patternIx = 0;
    _stepperData.patternIxInc = mode;         // positive direction
	#ifdef ESP8266
		_stepperData.aCycSteps = 0; // means no step
		_stepperData.tCycSteps = _stepperData.aCycSteps; 
	#else
		_stepperData.aCycSteps = TIMERPERIODE; //MIN_STEPTIME/CYCLETIME; 
		_stepperData.tCycSteps = _stepperData.aCycSteps; 
	#endif
	#ifndef IS_32BIT
	    _stepperData.tCycRemain = 0;                // work with remainder when cruising ( only 8-bit processors )
	#endif
    _stepperData.stepsFromZero = 0;
    _stepperData.rampState = rampStat::INACTIVE;
    _stepperData.stepRampLen             = 0;               // initialize with no acceleration  
    _stepperData.delayActiv = false;            // enable delaytime is runnung ( only ESP)
    _stepperData.output = NO_OUTPUT;          // unknown, not attached yet
    _stepperData.enablePin = 255;             // without enable
    _stepperData.nextStepperDataP = NULL;
	#ifndef ESP8266
    // add at end of chain
    stepperData_t **tmpPP = &stepperRootP;
    while ( *tmpPP != NULL ) tmpPP = &((*tmpPP)->nextStepperDataP);
    *tmpPP = &_stepperData;
	#endif
    if( _stepperCount++ >= MAX_STEPPER )  {
        stepMode = NOSTEP;      // invalid instance ( too mach objects )
    }
    
}
long MoToStepper::getSFZ() {
    // get step-distance from zero point
    // irq must be disabled, because stepsFromZero is updated in interrupt
    noInterrupts();
    lastSFZ = _stepperData.stepsFromZero;
    interrupts();
    //digitalWrite(16,1);
    // in A4988 mode there is no difference between half/fullstep in counting steps
    return ( stepMode==A4988?lastSFZ:lastSFZ / stepMode);
}

bool MoToStepper::_chkRunning() {
    // is the stepper moving?
    bool tmp;
    _noStepIRQ();
    tmp = _stepperData.rampState >= rampStat::CRUISING ;//&& _stepperData.stepsInRamp > 0 ;
    _stepIRQ();
    return tmp;
}

// public functions -------------------
uint8_t MoToStepper::attach( byte stepP, byte dirP ) {
    // step motor driver A4988 is used
    byte pins[2];
    if ( stepMode != A4988 ) return 0;    // false mode
    DB_PRINT( "Attach4988, S=%d, D=%d", stepP, dirP );
    
    pins[0] = stepP;
    pins[1] = dirP;
    return MoToStepper::attach( A4988_PINS, pins );
}
#ifndef ESP8266
uint8_t MoToStepper::attach( byte pin1, byte pin2, byte pin3, byte pin4 ) {
    byte pins[4];
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin3;
    pins[3] = pin4;
    return MoToStepper::attach( SINGLE_PINS, pins );
}
uint8_t MoToStepper::attach(byte outArg) {
    return MoToStepper::attach( outArg, (byte *)NULL );
}
#endif
    
uint8_t MoToStepper::attach( byte outArg, byte pins[] ) {
    // outArg must be one of PIN8_11 ... SPI_4 or SINGLE_PINS, A4988_PINS
    if ( stepMode == NOSTEP ) { DB_PRINT("Attach: invalid Object ( Ix = %d)", _stepperIx ); return 0; }// Invalid object
	#ifdef ESP8266
		if ( outArg != A4988_PINS ) return 0;
        if ( pins[0] >15 || gpioUsed(pins[0] ) ) return 0; // pins cannot be negative because of uint8_t
        if ( pins[1] >15 || gpioUsed(pins[1] ) ) return 0;
        setGpio(pins[0]);    // mark pin as used
        setGpio(pins[1]);    // mark pin as used
	#endif
    uint8_t attachOK = true;
    switch ( outArg ) {
      #if defined PORTD && defined PORTB
      case PIN4_7:
        if ( MoToStepper::outputsUsed.pin4_7 ) {
            // output already in use
            attachOK = false;
        } else {
            // Port D initiieren, Pin4-7 as Output
            MoToStepper::outputsUsed.pin4_7 = true;
            DDRD |= 0xf0;
            PORTD &= 0x0f;
        }
        break;
      case PIN8_11:
        if ( spiInitialized || MoToStepper::outputsUsed.pin8_11 ) {
            // PIN8_11 and SPI cannot be used simultaneously ( this is not true for Arduino mega )
            attachOK = false;
        } else {
            MoToStepper::outputsUsed.pin8_11 = true;
            DDRB |= 0x0f;
            PORTB &= 0xf0;
        }
        break;
      #endif
	  #ifndef ESP8266
      case SPI_1:
      case SPI_2:
      case SPI_3:
      case SPI_4:
        // check if already in use or if PIN8_11 is in use
        if ( (MoToStepper::outputsUsed.outputs & (1<<(outArg-1))) || MoToStepper::outputsUsed.pin8_11 ) {
            // incompatible!
            attachOK = false;
        } else {
            initSpiAS();
            MoToStepper::outputsUsed.outputs |= (1<<(outArg-1));
        }
        break;
      case SINGLE_PINS:
        // 4 single output pins - as yet there is no check if they are allowed!
        for ( byte i = 0; i<4; i++ ) {
            #ifdef FAST_PORTWRT
            // compute portadress and bitnumber
            _stepperData.portPins[i].Adr = (byte *) pgm_read_word_near(&port_to_output_PGM[pgm_read_byte_near(&digital_pin_to_port_PGM[ pins[i]])]);
            _stepperData.portPins[i].Mask = pgm_read_byte_near(&digital_pin_to_bit_mask_PGM[pins[i]]);
            #else // store pins directly
            _stepperData.pins[i] = pins[i];
            #endif
            pinMode( pins[i], OUTPUT );
            digitalWrite( pins[i], LOW );
        }
        break;
	  #endif // no ESP8266
      case A4988_PINS:
        // 2 single output pins (step and direction) - as yet there is no check if they are allowed!
        for ( byte i = 0; i<2; i++ ) {
            #ifdef FAST_PORTWRT
            // compute portadress and bitnumber
            _stepperData.portPins[i].Adr = (byte *) pgm_read_word_near(&port_to_output_PGM[pgm_read_byte_near(&digital_pin_to_port_PGM[ pins[i]])]);
            _stepperData.portPins[i].Mask = pgm_read_byte_near(&digital_pin_to_bit_mask_PGM[pins[i]]);
            #else // store pins directly
            _stepperData.pins[i] = pins[i];
            #endif
            pinMode( pins[i], OUTPUT );
            digitalWrite( pins[i], LOW );
        }
		_stepperData.patternIxInc = 1;  // defines direction
        break;
     default:
        // invalid Arg
        attachOK = false;
    }
    if ( attachOK ) {
        _stepperData.output = outArg;
        _stepperData.rampState = rampStat::STOPPED;
        setSpeedSteps( DEF_SPEEDSTEPS, DEF_RAMP );
        seizeTimerAS();
        enableStepperIsrAS();
    }
    DB_PRINT( "attach: output=%d, attachOK=%d", _stepperData.output, attachOK );
    //Serial.print( "Attach Stepper, Ix= "); Serial.println( _stepperIx );
    return attachOK;
}

void MoToStepper::detach() {   // no more moving, detach from output
    if ( _stepperData.output == NO_OUTPUT ) return ; // not attached
    // reconfigure stepper pins as INPUT ( state of RESET )
    // in FAST_PORTWRT mode this is not done, because the necessary Information is not stored
    #ifdef FAST_PORTWRT
    byte nPins=2;
    #endif
    switch ( _stepperData.output ) {
      #if defined PORTD && defined PORTB
      case PIN4_7:
        DDRD &= 0x0f;   // Port D Pin4-7 as Input
        PORTD &= 0x0f;  // Pullups off
        break;
      case PIN8_11:
        DDRB &= 0xf0;   // Port B Pin0-3 as Input
        PORTB &= 0xf0;  // Pullups off
        break;
      #endif
      #ifdef FAST_PORTWRT
      case SINGLE_PINS:
        nPins+=2;           // we have 2 more pins in Mode SINGLE_PINS compared to A4988Pins (  fallthrough to next case )
        [[fallthrough]];    // supress warning
      case A4988_PINS:
        for ( byte i=0; i<nPins; i++ ) {
            *(_stepperData.portPins[i].Adr-1) &= ~_stepperData.portPins[i].Mask;
            *(_stepperData.portPins[i].Adr) &= ~_stepperData.portPins[i].Mask;
        }
        break;
      #else
	  #ifndef ESP8266
      case SINGLE_PINS:
        // 4 single output pins
           pinMode( _stepperData.pins[3], INPUT );
           pinMode( _stepperData.pins[2], INPUT );
	  #endif
      case A4988_PINS: // only pins 0/1 
           pinMode( _stepperData.pins[1], INPUT );
           pinMode( _stepperData.pins[0], INPUT );
        break;
      #endif
      default:
        ;   // no action with SPI Outputs
    }
    _stepperData.output = NO_OUTPUT;
    _stepperData.rampState = rampStat::STOPPED;
    // detach enable if active
	#ifdef ESP8266
		// detach interrupts
		detachInterrupt( _stepperData.pins[0]);
        clrGpio(_stepperData.pins[0]);    // mark pin as unused
        clrGpio(_stepperData.pins[1]);    // mark pin as unused
        if ( _stepperData.enablePin != 255 ) {
            pinMode( _stepperData.enablePin, INPUT );
            clrGpio(_stepperData.enablePin);    // mark pin as unused
            detachInterrupt( _stepperData.enablePin);
            _stepperData.enablePin = 255;
        }
    #else
    if ( _stepperData.enablePin != 255 ) {
        pinMode( _stepperData.enablePin, INPUT );
        _stepperData.enablePin = 255;
    }
	#endif
}

void MoToStepper::attachEnable( uint8_t enablePin, uint16_t delay, bool active ) {
    // define an enable pin. enable is active as long as the motor moves.
    _stepperData.enablePin = enablePin;
    _stepperData.enable = active;       // defines whether activ is HIGH or LOW
    pinMode( enablePin, OUTPUT );
    digitalWrite( enablePin, !active );
    DB_PRINT("Enable, pin=%d, state=%d", enablePin, !active );
    #ifdef ESP8266
    // initialize ISR-Table and attach interrupt to dir-Pin
    // assign an ISR to the pin
        gpioTab[gpio2ISRx(_stepperData.pins[1])].MoToISR = (void (*)(void*))ISR_StepperEnable;
        gpioTab[gpio2ISRx(_stepperData.pins[1])].IsrData = &_stepperData;
        attachInterrupt( _stepperData.pins[1], gpioTab[gpio2ISRx(_stepperData.pins[1])].gpioISR, FALLING );
        setGpio(_stepperData.enablePin);    // mark pin as used
        _stepperData.cycDelay = delay;      // delay (ms) between enablePin HIGH/LOW and stepper moving
    #else
    _stepperData.cycDelay = 1000L * delay / CYCLETIME;      // delay ( in cycles ) between enablePin HIGH/LOW and stepper moving
    #endif
    }

int MoToStepper::setSpeed( int rpm10 ) {
    // Set speed in rpm*10. Step time is computed internally based on CYCLETIME and
    // steps per full rotation (stepsRev)
    if ( _stepperData.output == NO_OUTPUT ) return 0 ; // not attached
    return setSpeedSteps( min( 1000000L / MIN_STEPTIME * 10, (long)rpm10 * stepsRev / 60 ) ) ;
}

uintxx_t MoToStepper::setSpeedSteps( uintxx_t speed10 ) {
    // Speed in steps per sec * 10
    // without a new ramplen, the ramplen is adjusted according to the speedchange
    speed10 = min( uintxx_t(1000000L / MIN_STEPTIME * 10), speed10 );
    #ifdef IS_32BIT
    long rtmp = (uint64_t)speed10*_lastRampLen/_lastRampSpeed;
    #else
    long rtmp = (long)speed10*_lastRampLen/_lastRampSpeed;
    #endif
    DB_PRINT(">>>>>>>>>>>sSS:(%u) nRl=%ld", (unsigned int)speed10, rtmp );
    return setSpeedSteps( speed10,  -rtmp-1 );
}

uintxx_t MoToStepper::setRampLen( uintxx_t rampSteps ) {
    // set length of ramp ( from stop to actual target speed ) in steps
    return setSpeedSteps( _stepSpeed10, rampSteps );
}


uintxx_t MoToStepper::getSpeedSteps( ) {
	// return actual speed in steps/ 10sec 
	
    if ( _stepperData.output == NO_OUTPUT ) return -1; // not attached
    #ifdef IS_32BIT
	    // there is no remainder on 32bit systems annd aCycSteps is in µs
        uint32_t actSpeedSteps = 0;
        noInterrupts();
        actSpeedSteps = _stepperData.aCycSteps;
        interrupts();
        if ( actSpeedSteps > 0 ) actSpeedSteps = 10000000 / actSpeedSteps;
    #else
        uint16_t actSpeedSteps = 0;
        // get actual values from ISR
        uint16_t aCycSteps ;
        uint16_t aCycRemain ;
        _noStepIRQ();
        uint16_t stepsInRamp = _stepperData.stepsInRamp;
        rampStat rampState = _stepperData.rampState;
        #ifdef debugPrint
        //uint16_t aCycSteps = _stepperData.aCycSteps;
        //uint16_t aCycRemain = _stepperData.aCycRemain;
        uint16_t tCycSteps = _stepperData.tCycSteps;
        uint16_t tCycRemain = _stepperData.tCycRemain;
        #endif
        _stepIRQ();
        if ( rampState == rampStat::CRUISING ) {
            // stepper is moving with target speed
            actSpeedSteps = _stepSpeed10;
        } else if ( rampState > rampStat::STOPPED ) {
            // we are in a ramp
            aCycSteps = _stepperData.cyctXramplen / (stepsInRamp + RAMPOFFSET ) ;
            aCycRemain = _stepperData.cyctXramplen % (stepsInRamp + RAMPOFFSET);

            actSpeedSteps = 1000000L * 10 / ( (long)aCycSteps*CYCLETIME + (long)aCycRemain*CYCLETIME/(stepsInRamp + RAMPOFFSET ) );
        }
        DB_PRINT( "Acyc=%5d, Arem=%5d, SiR=%d, ( Tcyc=%5d, Trem=%5d ) ", aCycSteps, aCycRemain, stepsInRamp, tCycSteps, tCycRemain );
    #endif
	return actSpeedSteps;
}

void MoToStepper::doSteps( long stepValue) {
    _doSteps( stepValue, 0 );
}

void MoToStepper::_doSteps( long stepValue, bool absPos ) {
    // rotate stepValue steps
    // if the motor is already moving, this is counted from the actual position.
    // This means in ramp mode the motor may go beyond the desired position and than turn backwards 
    // to reach the targetposition ( stepValue steps away from actual position ) .

    long stepCnt;                 // nmbr of steps to take
    int8_t patternIxInc;
    #ifdef ESP8266
    int8_t startMove = 0;       // for ESP8266: create first pulse
    #endif
    
    if ( _stepperData.output == NO_OUTPUT ) return; // not attached
	//SET_TP1;
    //Serial.print( "doSteps: " ); Serial.println( stepValue );
    DB_PRINT(">>>>>>>>>>doSteps(%ld)>>>>>>>>>>>>>>>", stepValue );
    stepsToMove = stepValue;
    stepCnt = abs(stepValue);
    
    if ( _stepperData.stepRampLen > 0 || _stepperData.rampState == rampStat::SPEEDDECEL ) {
        // stepping with ramp
        
        if ( _chkRunning() ) {  // is the stepper moving?
            // yes, check if direction is to change
            //ToDo: check if we are in a ramp with stepCnt2 already set.
            if (  ( _stepperData.patternIxInc > 0 && stepValue > 0 ) || ( _stepperData.patternIxInc < 0 && stepValue < 0 ) ) {
                // no change in Direction
                _noStepIRQ();
                //digitalWrite(16,0);
                // When moving to abs position, adjust stepCnt if there have been new steps
                if ( absPos ) stepCnt -= abs( _stepperData.stepsFromZero-lastSFZ );
                if ( _stepperData.rampState == rampStat::SPEEDDECEL ) {
                    // we are already reducing speed, compute nbr of steps to stop
                    uint16_t stepsToStop = _stepperData.stepRampLen + (_stepperData.stepsInRamp-_stepperData.stepRampLen)/_stepperData.deltaSteps;
                    if ( stepCnt < stepsToStop  ) {
                        // cannot reach target -> still reducing speed, than ramp, than reverse
                        _stepperData.stepCnt = stepsToStop;
                        _stepperData.stepCnt2 = stepsToStop-stepCnt;
                        // no state change!
                    }
                } else if ( stepCnt <= (long)_stepperData.stepsInRamp ) {
                    // We cannot reach target whitin actual ramp. So go beyond target and than back.
                    _stepperData.stepCnt = _stepperData.stepsInRamp+1;
                    _stepperData.stepCnt2 = _stepperData.stepCnt-stepCnt;
                    _stepperData.rampState = rampStat::RAMPDECEL;
                } else { 
                    _stepperData.stepCnt = stepCnt;
                }
                _stepIRQ();
                //DB_PRINT( "StateErr1:, sCnt=%ld, sCnt2=%ld, sMove=%ld, aCyc=%d", _stepperData.stepCnt, _stepperData.stepCnt2, stepsToMove, _stepperData.aCycSteps );
            } else {
                // direction changes, stop and go backwards
                _noStepIRQ();
                //digitalWrite(16,0);
                //Schritte bis zum anhalten
                // When moving to abs position, adjust stepCnt if there have been new steps
                if ( absPos ) stepCnt += abs( _stepperData.stepsFromZero-lastSFZ );
                uintxx_t stepsToStop = _stepperData.stepsInRamp+1;
                if ( _stepperData.rampState == rampStat::SPEEDDECEL ) {
                    // we are already reducing speed, recompute nbr of steps to stop
                    stepsToStop = _stepperData.stepRampLen + (_stepperData.stepsInRamp-_stepperData.stepRampLen)/_stepperData.deltaSteps;
                } else {
                    _stepperData.rampState = rampStat::RAMPDECEL;
                }
                _stepperData.stepCnt = stepsToStop;
                // Schritte vom Stoppunkt bis zum eigentlichen Ziel
                _stepperData.stepCnt2 = _stepperData.stepCnt+stepCnt;
                _stepIRQ();
                //DB_PRINT( "Dir-Change:, sCnt=%ld, sCnt2=%ld, sMove=%ld, aCyc=%d", _stepperData.stepCnt, _stepperData.stepCnt2, stepsToMove, _stepperData.aCycSteps );
            }
        } else {
            // stepper does not move -> start a new move
            if ( stepValue != 0 ) {
                // we must move
                if ( stepValue > 0 ) patternIxInc = abs( _stepperData.patternIxInc );
                else     patternIxInc = -abs( _stepperData.patternIxInc );
                
                _noStepIRQ();
                #ifdef ESP8266
                    _stepperData.aCycSteps       = _stepperData.cyctXramplen / RAMPOFFSET; // first steplen in ramp
                    _stepperData.rampState      = rampStat::RAMPACCEL;
                    //digitalWrite( _stepperData.pins[1], patternIxInc<0 );      // setze dir-output
                    startMove = 1;
                #else
                    _stepperData.cycCnt         = 0;            // start with the next IRQ
                    _stepperData.aCycSteps      = MIN_START_CYCLES;
					#ifndef IS_32BIT
                    _stepperData.aCycRemain     = 0;  
					#endif
                    //#ifndef ESP8266
                    if ( _stepperData.enablePin != 255 ) {
                        // set enable pin to active and start delaytime
                        digitalWrite( _stepperData.enablePin, _stepperData.enable );
                        _stepperData.rampState      = rampStat::STARTING;
                    } else {
                        // no delay
                        _stepperData.rampState      = rampStat::RAMPACCEL;
                    }
                    //#endif
                #endif
                _stepperData.patternIxInc   = patternIxInc;
                _stepperData.stepsInRamp    = 0;
                _stepperData.stepCnt        = stepCnt;
                _stepIRQ();
                DB_PRINT("New Move: Steps:%ld, Enable=%d - State=%s(%d)", (long)stepValue, (int)digitalRead(_stepperData.enablePin) , rsC[(int)_stepperData.rampState],(int)_stepperData.rampState );
            }
        }
    } else {
        // no ramp
        if ( stepValue > 0 ) patternIxInc = abs( _stepperData.patternIxInc );
        else     patternIxInc = -abs( _stepperData.patternIxInc );
        _noStepIRQ();
        //digitalWrite(16,0);
        // When moving to abs position, adjust stepCnt if there have been new steps
        if ( absPos ) stepCnt = abs( stepValue + lastSFZ - _stepperData.stepsFromZero );
        _stepperData.patternIxInc = patternIxInc;
        _stepperData.stepCnt = stepCnt;
        if ( stepValue == 0 ) {
            // No steps to do and without Ramp: immediate stop
            _stepperData.rampState = rampStat::STOPPED;
            #ifdef ESP8266
            stopWaveformMoTo(_stepperData.pins[0]);
            #endif
        } else if ( _stepperData.rampState < rampStat::CRUISING  ) {
            // stepper does not move, start it because we have to do steps
            #ifdef ESP8266
				_stepperData.rampState      = rampStat::CRUISING;   // we don't have a ramp
				_stepperData.aCycSteps       = _stepperData.tCycSteps;
				startMove = 1;
            #else
				_stepperData.cycCnt         = 0;            // start with the next IRQ
				_stepperData.aCycSteps      = MIN_START_CYCLES;
				#ifndef IS_32BIT
				_stepperData.aCycRemain     = 0; 
				#endif
				if ( _stepperData.enablePin != 255 ) {
					// set enable pin to active and start delaytime
					digitalWrite( _stepperData.enablePin, _stepperData.enable );
					_stepperData.rampState      = rampStat::STARTING;
				} else {
					// no delay
					_stepperData.rampState      = rampStat::CRUISING;
				}
            #endif
        }
        _stepIRQ();
        //DB_PRINT( "NoRamp:, sCnt=%ld, sCnt2=%ld, sMove=%ld, aCyc=%d", _stepperData.stepCnt, _stepperData.stepCnt2, stepsToMove, _stepperData.aCycSteps );

    }
    
    #ifdef ESP8266
    if ( startMove ) {
        // check if enable Pin must be activated
        if ( _stepperData.enablePin !=255 ) {
            if ( !_stepperData.delayActiv ) {
                // enable must be set and delaytime is not yet running
                digitalWrite( _stepperData.enablePin, _stepperData.enable );
                // create a singlepulse on dir-output to measure delaytime
                //delayMicroseconds( 10 );
                startWaveformMoTo( _stepperData.pins[1], 1000*_stepperData.cycDelay, 10000 , 1000*_stepperData.cycDelay); 
                _stepperData.delayActiv = true;
            }
        } else {
            // no enable control, start movement directly
            // set dir output
            digitalWrite( _stepperData.pins[1], (_stepperData.patternIxInc < 0) );
            startWaveformMoTo( _stepperData.pins[0], CYCLETIME, _stepperData.aCycSteps-CYCLETIME, 0 ); 
        }
    } else {
        // direction may have changed, so set it here
        noInterrupts(); // with ramp direction may change in ISR
        digitalWrite( _stepperData.pins[1], (_stepperData.patternIxInc < 0) );
        interrupts();
    }
    DB_PRINT( "newStepValues:, sMove=%ld, Speed10=%d", stepsToMove,  _stepSpeed10  );
    #else
    //DB_PRINT( "StepValues:, sCnt=%ld, sCnt2=%ld, sMove=%ld, aCyc=%d", _stepperData.stepCnt, _stepperData.stepCnt2, stepsToMove, _stepperData.aCycSteps );
    //DB_PRINT( "RampValues:, Spd=%u, rmpLen=%u, tcyc=%u, trest=%u, acyc=%u", _stepSpeed10, _stepperData.stepRampLen,
    //                _stepperData.tCycSteps, _stepperData.tCycRemain, _stepperData.aCycSteps );
    //DB_PRINT( "   - State=%s, Rampsteps=%u" , rsC[_stepperData.rampState], _stepperData.stepsInRamp );
    #endif
    prDynData();
	//CLR_TP1;
}


// set reference point for absolute positioning
void MoToStepper::setZero() {
    setZero(0);
}

void MoToStepper::setZero(long zeroPoint) {
    if ( _stepperData.output == NO_OUTPUT ) return; // not attached
    // in FULLSTEP mode the internal steps are twice the real steps
    if (stepMode==FULLSTEP) zeroPoint *= 2;
    noInterrupts();
    _stepperData.stepsFromZero = -zeroPoint;
    interrupts();
}

void MoToStepper::setZero(long zeroPoint, long steps360) {
    if ( _stepperData.output == NO_OUTPUT ) return; // not attached
    stepsRev = steps360;
    setZero( zeroPoint );
}

void MoToStepper::write(long angleArg ) {
    // set next position as angle, measured from last setZero() - point
    DB_PRINT("write: %d", (int)angleArg);
    MoToStepper::write( angleArg, 1 );
}

void MoToStepper::write( long angleArg, byte fact ) {
    // for better resolution. angelArg/fact = angle in degrees
    // typical: fact = 10, angleArg in .1 degrees
    if ( _stepperData.output == NO_OUTPUT ) return ; // not attached
    bool negative;
    long angle2steps;
    negative =  ( angleArg < 0 ) ;
    DB_PRINT( "angleArg: %d",(int)angleArg ); //DB_PRINT( " getSFZ: ", getSFZ() );
    //Serial.print( "Write: " ); Serial.println( angleArg );
    // full revolutions:
    angle2steps = abs(angleArg) / (360L * fact ) * (long)stepsRev;
    // + remaining steps in last revolution ( with rounding )
    angle2steps += (( abs(angleArg % (360L * fact) ) * (long)stepsRev ) + 180L*fact )/ ( 360L * fact)  ;
    //angle2steps =  ( (abs(angleArg) * (long)stepsRev*10) / ( 360L * fact) +5) /10 ;
    if ( negative ) angle2steps = -angle2steps;
    _doSteps(angle2steps  - getSFZ(), 1 );
}

void MoToStepper::writeSteps( long stepPos ) {
    // go to position stepPos steps away from zeropoint
    if ( _stepperData.output == NO_OUTPUT ) return; // not attached
    //digitalWrite(16,0);
    _doSteps(stepPos  - getSFZ(), 1 );
}

long MoToStepper::read()
{   // returns actual position as degree
    if ( _stepperData.output == NO_OUTPUT ) return 0; // not attached

    long tmp = getSFZ();
    bool negative;
    negative = ( tmp < 0 );
	tmp = (abs(tmp)/stepsRev*360) + (( (abs(tmp)%stepsRev) *3600L / stepsRev ) +5) / 10;
    if ( negative ) tmp = -tmp;
    return  tmp;
}

long MoToStepper::readSteps()
{   // returns actual position as steps
    if ( _stepperData.output == NO_OUTPUT ) return 0; // not attached

    return  getSFZ();
}


long MoToStepper::stepsToDo() { 
    // return remaining steps until target position
    long tmp;
    _noStepIRQ(); // disable Stepper interrupt, because (long)stepcnt is changed in TCR interrupt
    tmp = _stepperData.stepCnt + _stepperData.stepCnt2;
    _stepIRQ();  // enable stepper IRQ
    return tmp;
}

        
uint8_t MoToStepper::moving() {
    // return how much still to move (percentage)
    long tmp;
    if ( _stepperData.output == NO_OUTPUT ) return 0; // not attached
    //Serial.print( _stepperData.stepCnt ); Serial.print(" "); 
    //Serial.println( _stepperData.aCycSteps );
    _noStepIRQ(); // disable Stepper interrupt, because (long)stepcnt is changed in TCR interrupt
    tmp = _stepperData.stepCnt + _stepperData.stepCnt2;
    _stepIRQ();  // enable stepper IRQ
    if ( tmp > 0 ) {
        // do NOT return 0, even if less than 1%, because 0 means real stop of the motor
        if ( tmp < 2147483647L / 100 )
            tmp = (tmp * 100 / (abs( stepsToMove)+1) ) + 1;
        else
            tmp =  (tmp  / (( abs( stepsToMove)+1) / 100 ) ) + 1;
    }
    if ( tmp > 255 ) tmp=255;
    return tmp ;
}

void MoToStepper::rotate(int8_t direction) {
	// rotate endless ( not really, do maximum stepcount ;-)
    if ( _stepperData.output == NO_OUTPUT ) return; // not attached
    
	if (direction == 0 ) {
        if ( _stepperData.stepRampLen == 0 ) {
            // no ramp, identical to 'stop'
            stop();
        } else {
            // start decelerating
            _noStepIRQ();
            switch ( _stepperData.rampState ) {
              case rampStat::RAMPACCEL:
              case rampStat::SPEEDDECEL:
                _stepperData.stepCnt = _stepperData.stepsInRamp;
                DB_PRINT("rot:Accel");
                break;
              case rampStat::CRUISING:
                _stepperData.stepCnt = _stepperData.stepRampLen;
                //DB_PRINT( "rot: sCnt=%u\n\r", _stepperData.stepCnt );
                break;
              case rampStat::STARTING:
                // abort starting the stepper
                _stepperData.stepCnt = 1;
                break;
              default:
                DB_PRINT("rot0: already stopped");
                ; // already in Stop or decelerating - do nothing
            }
            stepsToMove = _stepperData.stepCnt;
            _stepperData.stepCnt2 = 0;      // No reverse moving after stop
            _stepIRQ(); 
        }
	} else if (direction > 0 ) { // ToDo: Grenzwerte sauber berechnen
        doSteps(  2147483646L - _stepperData.stepRampLen );
	} else {
        doSteps( -2147483646L + _stepperData.stepRampLen);
    }
    prDynData();
}

void MoToStepper::stop() {
	// immediate stop of the motor
    if ( _stepperData.output == NO_OUTPUT ) return; // not attached
    _noStepIRQ();
    if (  _stepperData.rampState >= rampStat::STARTING ) {
        // its moving, stopping with next pulse
        stepsToMove = 0;
        _stepperData.stepCnt = 1;
        DB_PRINT("Stopping!");
    }
    _stepIRQ();
}
