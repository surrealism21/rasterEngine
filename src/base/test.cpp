#include "raster.hpp"

class ac_test : public dBase_c {
    void onCreate();

    ofImage ronalds[24];
};

const Profile testProfile = Profile<ac_test>(ActorID::AC_Test);

void ac_test::onCreate() {

}