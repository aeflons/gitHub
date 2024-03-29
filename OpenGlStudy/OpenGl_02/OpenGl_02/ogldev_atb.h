#ifndef OGLDEV_ATB_H
#define	OGLDEV_ATB_H

#include "ogldev_keys.h"
#include "ogldev_math_3d.h"


class ATB
{
public:
    ATB();
    
    bool Init();
    
    bool KeyboardCB(OGLDEV_KEY OgldevKey);

    bool PassiveMouseCB(int x, int y);

    void RenderSceneCB();

    bool MouseCB(OGLDEV_MOUSE Button, OGLDEV_KEY_STATE State, int x, int y);
    
};




#endif
