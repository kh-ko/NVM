#ifndef UNITUTIL_H
#define UNITUTIL_H
#include <QObject>

#define UNITUTIL_CONVERT(x,y,z) UnitUtil::getInstance()->convert(x,y,z)
#define UNITUTIL_ADD_PRECISION(x,y) UnitUtil::getInstance()->getAdditionalPrecision(x,y)
#define UNITUTIL_TO_STR(x)      UnitUtil::getInstance()->toString(x)
#define UNITUTIL_STR_TO_INT(x)  UnitUtil::getInstance()->stringToUnit(x)

class UnitUtilEnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(ePressureUnit)

public:
    enum ePressureUnit{
        PRESSURE_UNIT_PA    = 0,
        PRESSURE_UNIT_BAR   = 1,
        PRESSURE_UNIT_MBAR  = 2,
        PRESSURE_UNIT_UBAR  = 3,
        PRESSURE_UNIT_TORR  = 4,
        PRESSURE_UNIT_MTORR = 5,
        PRESSURE_UNIT_ATM   = 6,
        PRESSURE_UNIT_PSI   = 7,
        PRESSURE_UNIT_PSF   = 8,
        PRESSURE_UNIT_VOLT  = 9,
        PRESSURE_UNIT_MVOLT = 10
    };
};

class UnitUtil
{
public:
                                        //     pa     ,     bar     ,     mbar    ,    ubar    ,     torr     ,     mtorr   ,     atm     ,     psi     ,     psf
    const double convertFactor[9][9] =    {{            1,      0.00001,         0.01,           10,     0.007501,        7.501,  0.000009869,     0.000145,     0.02089},  // pa
                                           {       100000,            1,         1000,      1000000,        750.1,       750100,       0.9869,         14.5,        2089},  // bar
                                           {          100,        0.001,            1,         1000,       0.7501,        750.1,    0.0009869,       0.0145,       2.089},  // mbar
                                           {          0.1,     0.000001,        0.001,            1,    0.0007501,       0.7501, 0.0000009869,    0.0000145,    0.002089},  // ubar
                                           {       133.32,    0.0013332,       1.3332,       1333.2,            1,         1000,    0.0013158,      0.01934,      2.7845},  // Torr
                                           {      0.13332, 0.0000013332,    0.0013332,       1.3332,        0.001,            1, 0.0000013158,   0.00001934,   0.0027845},  // mTorr
                                           {       101325,      1.01325,      1013.25,      1013250,      760.002,       760002,            1,         14.7,        2116},  // atm
                                           {         6895,      0.06895,        68.95,        68950,       51.715,        51715,      0.06805,            1,         144},  // psi
                                           {        47.88,    0.0004788,       0.4788,        478.8,       0.3591,        359.1,    0.0004725,     0.006944,           1}}; // psf


    const int   convertFactorPrec[9][9] = {{            0,           -5,           -2,            1,           -3,            0,           -6,           -4,          -2},  // pa
                                           {            5,            0,            3,            6,            2,            5,           -1,            1,           3},  // bar
                                           {            2,           -3,            0,            3,           -1,            2,           -4,           -2,           0},  // mbar
                                           {           -1,           -6,           -3,            0,           -4,           -1,           -7,           -5,          -3},  // ubar
                                           {            2,           -3,            0,            3,            0,            3,           -3,           -2,           0},  // Torr
                                           {           -1,           -6,           -3,            0,           -3,            0,           -6,           -5,          -3},  // mTorr
                                           {            5,            0,            3,            6,            2,            5,            0,            1,           3},  // atm
                                           {            3,           -2,            1,            4,            1,            4,           -2,            0,           2},  // psi
                                           {            1,           -4,           -1,            2,           -1,            2,           -4,           -3,           0}}; // psf

public:
    static UnitUtil * getInstance()
    {
        static UnitUtil *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new UnitUtil();
        }

        return mpSelf;
    }

    double convert(int unit01, double value, int unit02)
    {
        return convertFactor[unit01][unit02] * value;
    }

    int getAdditionalPrecision(int unit01, int unit02)
    {
        return convertFactorPrec[unit01][unit02] * -1;
    }

    QString toString(int unit)
    {
        switch (unit) {
        case UnitUtilEnumDef::PRESSURE_UNIT_PA    : return "Pa"   ;
        case UnitUtilEnumDef::PRESSURE_UNIT_BAR   : return "bar"  ;
        case UnitUtilEnumDef::PRESSURE_UNIT_MBAR  : return "mbar" ;
        case UnitUtilEnumDef::PRESSURE_UNIT_UBAR  : return "ubar" ;
        case UnitUtilEnumDef::PRESSURE_UNIT_TORR  : return "Torr" ;
        case UnitUtilEnumDef::PRESSURE_UNIT_MTORR : return "mTorr";
        case UnitUtilEnumDef::PRESSURE_UNIT_ATM   : return "atm"  ;
        case UnitUtilEnumDef::PRESSURE_UNIT_PSI   : return "psi"  ;
        case UnitUtilEnumDef::PRESSURE_UNIT_PSF   : return "psf"  ;
        default : return "";
        }
    }

    int stringToUnit(QString unitStr)
    {
        if     (unitStr.startsWith("Pa"   )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_PA   ;}
        else if(unitStr.startsWith("bar"  )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_BAR  ;}
        else if(unitStr.startsWith("mbar" )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_MBAR ;}
        else if(unitStr.startsWith("ubar" )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_UBAR ;}
        else if(unitStr.startsWith("Torr" )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_TORR ;}
        else if(unitStr.startsWith("mTorr")){return (int)UnitUtilEnumDef::PRESSURE_UNIT_MTORR;}
        else if(unitStr.startsWith("atm"  )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_ATM  ;}
        else if(unitStr.startsWith("psi"  )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_PSI  ;}
        else if(unitStr.startsWith("psf"  )){return (int)UnitUtilEnumDef::PRESSURE_UNIT_PSF  ;}
        else                                {return -1;                                       }
    }

    UnitUtil(){}
    ~UnitUtil(){}


};
#endif // UNITUTIL_H
