#include "sensorController.h"
#include <Particle.h>
#include "scComInterface.h"
#include "channel/BaseChannel.h"

namespace sensorController {

    namespace {

        BaseChannel<bool> hasGPSfix = BaseChannel<bool>::get("hasGPSfix");
        BaseChannel<float> latitude = BaseChannel<float>::get("latitude");
        BaseChannel<float> longitude = BaseChannel<float>::get("longitude");
        BaseChannel<float> tepmperature1 = BaseChannel<float>::get("tepmperature1");
        BaseChannel<float> tepmperature2 = BaseChannel<float>::get("tepmperature2");
        BaseChannel<float> tepmperature3 = BaseChannel<float>::get("tepmperature3");
        BaseChannel<float> tepmperature4 = BaseChannel<float>::get("tepmperature4");
        
        BaseChannel<int> buckPWM = BaseChannel<int>::get("buckPWM");
        
        BaseChannel<float> cellVoltage1 = BaseChannel<float>::get("cellVoltage1");
        BaseChannel<float> cellVoltage2 = BaseChannel<float>::get("cellVoltage2");
        BaseChannel<float> cellVoltage3 = BaseChannel<float>::get("cellVoltage3");
        BaseChannel<float> cellVoltage4 = BaseChannel<float>::get("cellVoltage4");
        BaseChannel<float> solarVoltageN = BaseChannel<float>::get("solarVoltageN");
        BaseChannel<float> solarVoltageP = BaseChannel<float>::get("solarVoltageP");
        BaseChannel<float> buckCurrent = BaseChannel<float>::get("buckCurrent");
        BaseChannel<float> systemCurrent = BaseChannel<float>::get("systemCurrent");
        BaseChannel<float> motorCurrent1 = BaseChannel<float>::get("motorCurrent1");
        BaseChannel<float> motorCurrent2 = BaseChannel<float>::get("motorCurrent2");

        SCDataFrame dataFrame;

        void receiveEvent(int howMany) {
            Serial.println(howMany);
            Wire.readBytes((char*) dataFrame.data, SC_FULL_DATA_FRAME_LENGTH);

            hasGPSfix.setValue(dataFrame.full.hasGPSfix);
            latitude.setValue(dataFrame.full.latitude);
            longitude.setValue(dataFrame.full.longitude);
            tepmperature1.setValue(dataFrame.full.tepmperature1 / 256.0);
            tepmperature2.setValue(dataFrame.full.tepmperature2 / 256.0);
            tepmperature3.setValue(dataFrame.full.tepmperature3 / 256.0);
            tepmperature4.setValue(dataFrame.full.tepmperature4 / 256.0);
            buckPWM.setValue(dataFrame.full.buckPWM);
            cellVoltage1.setValue(dataFrame.full.cellVoltage1 / 256.0);
            cellVoltage2.setValue(dataFrame.full.cellVoltage2 / 256.0);
            cellVoltage3.setValue(dataFrame.full.cellVoltage3 / 256.0);
            cellVoltage4.setValue(dataFrame.full.cellVoltage4 / 256.0);
            solarVoltageN.setValue(dataFrame.full.solarVoltageN / 256.0);
            solarVoltageP.setValue(dataFrame.full.solarVoltageP / 256.0);
            buckCurrent.setValue(dataFrame.full.buckCurrent / 256.0);
            systemCurrent.setValue(dataFrame.full.systemCurrent / 256.0);
            motorCurrent1.setValue(dataFrame.full.motorCurrent1 / 256.0);
            motorCurrent2.setValue(dataFrame.full.motorCurrent2 / 256.0);

            Serial.println(dataFrame.full.tepmperature1 / 256.0);
            //Serial.printlnf("temp1: %f, temp2: %f, temp3: %f, temp4: %f", dataFrame.full.tepmperature1 / 256.0
            //      , dataFrame.full.tepmperature2 / 256.0, dataFrame.full.tepmperature3 / 256.0, dataFrame.full.tepmperature4 / 256.0);
        }

    }

    void begin() {
        Wire.begin(BORON_I2C_ADDRESS);
        Wire.onReceive(receiveEvent);
    }

}