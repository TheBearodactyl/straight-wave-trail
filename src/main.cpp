#include "Geode/modify/Modify.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

float phase;

struct StraightWaveTrail : Modify<StraightWaveTrail, PlayLayer> {
  void postUpdate(float p0) { 
    bool enable = Mod::get()->getSettingValue<bool>("enable");
    float speed = Mod::get()->getSettingValue<double>("speed");

    phase = fmod(phase + speed, 360.f);

    _ccColor3B color = get_checkers(phase, 0, true, ccColor3B{0,0,0}, ccColor3B{255,255,255});

    if (enable) {
      this->m_player1->m_waveTrail->setColor(color);
      this->m_player2->m_waveTrail->setColor(color);
    }

    PlayLayer::postUpdate(p0); 
  }

  cocos2d::_ccColor3B get_checkers(float &phase, float offset, bool smooth, ccColor3B c1, ccColor3B c2) {
    float t = fmodf(phase + offset, 360.0f);
    float y = t / 360.0f; // Normalize to [0, 1] range

    cocos2d::_ccColor3B out;

    out.r = static_cast<GLubyte>(c1.r + (c2.r - c1.r) * y);
    out.g = static_cast<GLubyte>(c1.g + (c2.g - c1.g) * y);
    out.b = static_cast<GLubyte>(c1.b + (c2.b - c1.b) * y);

    return out;
}

};
