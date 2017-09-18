#include "ElEInput.h"

ElEInput* ElEInput::instance = nullptr;

ElEbool ElEInput::keyPressed(const ElEKey& key)
{
#ifdef RASPBERRY_COMPILE
    if(kbfd == -1)
    {
        DIR             *dirp = nullptr;
        struct dirent  *dp = nullptr;
        regex_t         kbd,
                        mouse;
        ElEchar         fullPath[1024];
        static ElEchar  *dirName = "/dev/input/by-id";
        ElEint          result;
        if(regcomp(&kbd, "event-kbd", 0) != 0)
        {
            printf("regcomp for kbd failed\n");
            return ElEfalse;
        }
        if(regcomp(&mouse, "event-mouse", 0) != 0)
        {
            printf("regcomp for kbd failed\n");
            return ElEfalse;
        }
        if((dirp = opendir(dirName)) == nullptr)
        {
            perror("couldn't open '/dev/input/by-id'");
            return ElEfalse;
        }
        do
        {
            errno = 0;
            if((dp = readdir(dirp)) != nullptr)
            {
                if(regexec (&kbd, dp->d_name, 0, NULL, 0) == 0)
                {
                    sprintf(fullPath,"%s/%s",dirName,dp->d_name);
                    kbfd = open(fullPath, O_RDONLY | O_NONBLOCK);
                    result  = ioctl(kbfd, EVIOCGRAB, 1);
                }
                if(regexec (&mouse, dp->d_name, 0, NULL, 0) == 0)
                {
                    sprintf(fullPath,"%s/%s",dirName,dp->d_name);
                    mfd = open(fullPath, O_RDONLY | O_NONBLOCK);
                    result  = ioctl(mfd, EVIOCGRAB, 1);
                }
            }
        }while (dp != nullptr);
        closedir(dirp);
        regfree(&kbd);
        regfree(&mouse);
    }
    struct input_event ev[64];
    ElEint rd = read(mfd,ev,sizeof(ev));
    if(rd > 0)
    {
        ElEint              count,
                            n;
        struct input_event *evp;
        count  = rd / sizeof(struct input_event);
        n = 0;
        while(count--)
        {
            evp = &ev[n++];
            if(evp->code == BTN_LEFT && key == mb_left)
            {
                if(evp->type == 1)
                {
                    if(evp->value == 1)
                        return ElEtrue;
                    else
                        return ElEfalse;
                }
            }
            else if(evp->code == BTN_RIGHT && key == mb_right)
            {
                if(evp->type == 1)
                {
                    if(evp->value == 1)
                        return ElEtrue;
                    else
                        return ElEfalse;
                }
            }
            else if(evp->code == BTN_MIDDLE && key == mb_middle)
            {
                if(evp->type == 1)
                {
                    if(evp->value == 1)
                        return ElEtrue;
                    else
                        return ElEfalse;
                }
            }
        }
    }

    rd = read(kbfd, ev, sizeof(ev));
    if(rd > 0)
    {
        ElEint              count,
                            n;
        struct input_event *evp;
        count  = rd / sizeof(struct input_event);
        n = 0;
        while(count--)
        {
            evp = &ev[n++];
            if(evp->type == 1)
            {
                if(evp->value == 1)
                {
                    if(evp->code == KEY_A && key == kb_A)
                        return ElEtrue;
                    else if(evp->code == KEY_B && key == kb_B)
                        return ElEtrue;
                    else if(evp->code == KEY_C && key == kb_C)
                        return ElEtrue;
                    else if(evp->code == KEY_D && key == kb_D)
                        return ElEtrue;
                    else if(evp->code == KEY_E && key == kb_E)
                        return ElEtrue;
                    else if(evp->code == KEY_F && key == kb_F)
                        return ElEtrue;
                    else if(evp->code == KEY_G && key == kb_G)
                        return ElEtrue;
                    else if(evp->code == KEY_H && key == kb_H)
                        return ElEtrue;
                    else if(evp->code == KEY_I && key == kb_I)
                        return ElEtrue;
                    else if(evp->code == KEY_J && key == kb_J)
                        return ElEtrue;
                    else if(evp->code == KEY_K && key == kb_K)
                        return ElEtrue;
                    else if(evp->code == KEY_L && key == kb_L)
                        return ElEtrue;
                    else if(evp->code == KEY_M && key == kb_M)
                        return ElEtrue;
                    else if(evp->code == KEY_N && key == kb_N)
                        return ElEtrue;
                    else if(evp->code == KEY_O && key == kb_O)
                        return ElEtrue;
                    else if(evp->code == KEY_P && key == kb_P)
                        return ElEtrue;
                    else if(evp->code == KEY_Q && key == kb_Q)
                        return ElEtrue;
                    else if(evp->code == KEY_R && key == kb_R)
                        return ElEtrue;
                    else if(evp->code == KEY_S && key == kb_S)
                        return ElEtrue;
                    else if(evp->code == KEY_T && key == kb_T)
                        return ElEtrue;
                    else if(evp->code == KEY_U && key == kb_U)
                        return ElEtrue;
                    else if(evp->code == KEY_W && key == kb_W)
                        return ElEtrue;
                    else if(evp->code == KEY_X && key == kb_X)
                        return ElEtrue;
                    else if(evp->code == KEY_Y && key == kb_Y)
                        return ElEtrue;
                    else if(evp->code == KEY_Z && key == kb_Z)
                        return ElEtrue;
                    else if(evp->code == KEY_ESC && key == kb_esc)
                        return ElEtrue;
                    else if(evp->code == KEY_LEFTALT && key == kb_lalt)
                        return ElEtrue;
                    else if(evp->code == KEY_RIGHTALT && key == kb_ralt)
                        return ElEtrue;
                    else if(evp->code == KEY_LEFTSHIFT && key == kb_lshift)
                        return ElEtrue;
                    else if(evp->code == KEY_RIGHTSHIFT && key == kb_rshift)
                        return ElEtrue;
                    else if(evp->code == KEY_LEFTCTRL && key == kb_lctrl)
                        return ElEtrue;
                    else if(evp->code == KEY_RIGHTCTRL && key == kb_rctrl)
                        return ElEtrue;
                    else if(evp->code == KEY_ENTER && key == kb_return)
                        return ElEtrue;
                }
            }
        }
    }
#endif
    return ElEfalse;
}

ElEPosHelper ElEcall mousePosition()
{
#ifdef RASPBERRY_COMPILE

#endif
    return ElEPosHelper{0,0};
}
