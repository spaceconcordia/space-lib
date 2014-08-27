/*
 * =====================================================================================
 *
 *       Filename:  SystemProcess.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/26/2014 10:13:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef SYSTEMPROCESS_H
#define SYSTEMPROCESS_H

class SystemProcess {
    private :
        char * command;

    public :
        SystemProcess(char * command);
        std::string Execute();
};

#endif /* !SYSTEMPROCESS_H */
