///////////////////////////////////////////////////////////////
//
// CommandProcessing.cpp
//      implementation file for CommandProcessing.h
//
///////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////
#include "CommandProcessing.h"
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>

// GLOBAL VARIABLES ///////////////////////////////////////////
std::string G_GameState;
std::vector<std::string> T_GameState;

// COMMAND CLASS //////////////////////////////////////////////

// Default Constructor
Command::Command()
{
};

// Copy Constructor
Command::Command(const Command& acmd) : cmd(acmd.cmd), flags(acmd.flags), fn(acmd.fn), gamestate(acmd.gamestate), effect(acmd.effect)
{
};

// Copy Constructor
Command::Command(std::string cmd, std::string flg, std::string fn, std::string gs)
{
    this->cmd = cmd;            // copies over passed elements to this object
    this->flags = flg;
    this->fn = fn;
    this->gamestate = gs;

    // Automatically sets effect based on cmd
    if (cmd=="loadmap") { this->effect ="load the map file"; }
    if (cmd=="validatemap") { this->effect ="validate the map file"; }

    if (cmd=="addplayer") { this->effect ="add a player"; }

    if (cmd=="gamestart") { this->effect ="starts the game"; }
    if (cmd=="quit") { this->effect ="quit the game"; }
    if (cmd=="loadcmd") { this->effect ="load a list of valid commands from file"; }
    if (cmd=="runcmd") { this->effect ="runs commands from list in FCPA returns to console in resulting state"; }
    if (cmd=="changestate") { this->effect ="manually change the state to test code"; }
};

// Assignment Operator
Command& Command::operator=(const Command& acmd)
{
    if (this==&acmd)
    {
        return *this;
    }
    cmd = acmd.cmd;
    flags = acmd.flags;
    fn = acmd.fn;
    gamestate = acmd.gamestate;
    effect = acmd.effect;
    return *this;
};

// Stream Operator
std::ostream& operator<<(std::ostream& stream, const Command& acmd)
{
    stream << "| command = " << acmd.cmd << " | flag = " << acmd.flags << " | filename = " << acmd.fn << " | gamestate = " << acmd.gamestate << " | effect = " << acmd.effect;
    return stream;
};

// Getters
std::string Command::getCmd() { return cmd; };
std::string Command::getFlags() { return flags; };
std::string Command::getFn()  { return fn; };
std::string Command::getGs()  { return gamestate; };
std::string Command::getEffect() { return effect; }


///////////////////////////////////////////////////////////////

// COMMANDPROCESSING CLASS ////////////////////////////////////

// Default constructor
CommandProcessor::CommandProcessor()
{
    LogObserver* ob4 = new LogObserver();
    Attach(ob4);
}

// Copy Constructor
CommandProcessor::CommandProcessor(const CommandProcessor& acmdP)
{
}

// Assignment Operator
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& acmdP)
{
    if (this == &acmdP)
    {
        return *this;
    }
    listCmd = acmdP.listCmd;    // Copy the list of acmdP into listCmd of this object
    return *this;
}

// Stream Operator
std::ostream& operator<<(std::ostream& stream, const CommandProcessor& acmdP)
//std::ostream& operator<<(std::ostream& stream, const std::vector<Command*>& vals)
{
    if (acmdP.listCmd.size()!=0) {
        //stream << "List of valid issued commands : ";
        for (int i = 0; i < acmdP.listCmd.size(); i++) {
            std::string cmd = acmdP.listCmd.at(i)->getCmd();
            stream << "   [" << i << "] " << cmd;
        }
        stream << "\b\b";
    }else
    {
        std::cout<<"No commands in list."<<std::endl;
    }
    return stream;
}





// getOnlyCmd(string input) : helper function to get valid cmd from input
//      Returns one of {quit,loadmap,validatemap,gamestart,replay,loadcmd} error otherwise
std::string CommandProcessor::getOnlyCmd(std::string input)
{
    // Check if commands {quit,loadmap,validatemap,addplayer,gamestart,replay} exist at position 0. If not, error.

    //std::cout<<"Input passed is : "<<input<<std::endl;
    if (input.find("quit",0)!=std::string::npos) { return "quit"; };
    if (input.find("loadmap",0)!=std::string::npos) { return "loadmap"; };
    if (input.find("validatemap",0)!=std::string::npos) { return "validatemap"; };
    if (input.find("addplayer",0)!=std::string::npos) { return "addplayer"; };
    if (input.find("gamestart",0)!=std::string::npos) { return "gamestart"; };
    if (input.find("replay",0)!=std::string::npos) { return "replay"; };
    if (input.find("loadcmd",0)!=std::string::npos) { return "loadcmd"; };
    if (input.find("runcmd",0)!=std::string::npos) { return "runcmd"; }
    if (input.find("changestate",0)!=std::string::npos) { return "changestate"; };
    std::cout<<"cmd not found"<<std::endl;
    return "error";
}

// getOnlyFlag(string input) : helper function to get valid argument/flag from input
//      Returns one of {-file, -console} if this argument is passed. error otherwise.
std::string CommandProcessor::getOnlyFlag(std::string input)
{
    if (input.find("-file") != std::string::npos) { return "-file"; }
    if (input.find("-console") != std::string::npos) { return "-console"; }
    //std::cout<<"flag not found"<<std::endl;
    return "error";
}

// getOnlyThing(string input) : helper function to get <thing> from input
//      returns thing from <thing> if its in the input, error otherwise.
// return thing from <thing> in input
std::string CommandProcessor::getOnlyThing(std::string input)
{
    int sp = input.find("<");
    int i = sp;
    int ep = input.find(">");

    // Shimmy the indices
    sp+=1;
    ep=ep-1;

    // Adds some redundency that our commends are correct.
    // loadmap <thing>, return thing. Thing could be <filename>, <player>, or <mapfile> for commands given.
    if ( (getOnlyCmd(input)=="loadmap") || (getOnlyCmd(input)=="addplayer") || (getOnlyCmd(input)=="loadcmd") ) {
        // // This code peels off <thing>
        if (sp != std::string::npos && ep != std::string::npos) {
            std::string t_fn = input.substr(sp, ep - sp + 1);
            // std::cout<<"Filename starts at i="<<sp<<" ends at j="<<ep<<" and has name "<<t_fn<<std::endl;
            return t_fn;
        }else
        {
            return "error";
        }
    }
    return "error";
}

std::string CommandProcessor::stringToLog()
{
    return listCmd.back()->getCmd()+" "+listCmd.back()->getEffect();
}





// Initialize the game state
void CommandProcessor::initGs()
{
    // Initialize T_GameState;
    T_GameState.push_back("start");
    T_GameState.push_back("maploaded");
    T_GameState.push_back("mapvalidated");
    T_GameState.push_back("playersadded");
    T_GameState.push_back("win");
    T_GameState.push_back("exit program");

    // Initialize the start
    G_GameState = "start";
}

// updateGs(string cmd)
//       returns true if cmd is executable for the gamestate as it is. If so updates gamestate and returns true. else false.
bool CommandProcessor::updateGs(std::string cmd)
{
    if (G_GameState=="exit program")
    {
        std::cout<<"EXITING PROGRAM."<<std::endl;
        exit(1);
    }

    // Can be run independent of gamestate
    if (cmd=="loadcmd" || cmd=="runcmd") { return true; }

    // cmd : loadmap, state=start,maploaded (transition,recur)
    if (G_GameState=="start" && cmd=="loadmap") { G_GameState="maploaded";  return true; }
    if (G_GameState=="maploaded" && cmd=="loadmap") { G_GameState="maploaded"; return true; }

    // cmd : validatemap, state=maploadede (transition only)
    if (G_GameState=="maploaded" && cmd=="validatemap") { G_GameState="mapvalidated";  return true; }

    // cmd : addplayer, state=mapvalidated,playersadded (transition,recur)
    if (G_GameState=="mapvalidated" && cmd=="addplayer") { G_GameState="playersadded"; return true; }
    if (G_GameState=="playersadded" && cmd=="addplayer") { G_GameState="playersadded"; return true; }

    // cmd : gamestart, state=playersadded (transition only)
    if (G_GameState=="playersadded" && cmd=="gamestart") { G_GameState = "assignreinforcement"; return true; }

    // cmd: replay, state=win (transition only)
    if (G_GameState=="win" && cmd=="replay") { G_GameState = "start"; return true; }

    // cmd: quit, state=win (transition and exit)
    if (G_GameState=="win" && cmd=="quit")
    {
        G_GameState ="exit program";
        return true;
    }
    // If none of these cases, false.
    return false;
}

// validate(const std::string& input) : will return true if an input is a valid command or not (false)
//        cmd:{loadmap,addplayer,validatemap,gamestart,replay,quit}+thing:{mapfile,filename,player}
//    or  cmd:{loadcmd}+flag{-file}+{thing}
//    or  cmd:{loadcmd}+flag{-console}      does nothing as of yet, we're in the console (!)
bool CommandProcessor::validate(const std::string& inp)
{
    bool isvalidcmd = false;

    // Check if first word is a command.
    if (getOnlyCmd(inp)!="error")
    {
        // These ones are special cases and custom commands, handled externally.
        if (getOnlyCmd(inp)=="quit") { return true; }
        if (getOnlyCmd(inp)=="changestate") { return true; }

        if (getOnlyCmd(inp)=="loadcmd") { return true; }
        if (getOnlyCmd(inp)=="runcmd") { return true; }

        // These ones are singular commands so if its one of these, return true.
        if (getOnlyCmd(inp)=="validatemap" || getOnlyCmd(inp)=="gamestart" || getOnlyCmd(inp)=="replay" || getOnlyCmd(inp)=="quit")
        {
            // Check if the GS allows each of these to run.
            if (updateGs(getOnlyCmd(inp))) { return true; }
            return false;
        }

        // cmd : loadmap <mapfile> or addplayer <addplayer> check the wrap
        if (getOnlyCmd(inp)=="loadmap" || getOnlyCmd(inp)=="addplayer")
        {
            // Check for <something>, if so loadmap <something> or addplayer<something>. If state allows, true
            if ( (getOnlyThing(inp)!="error") && (updateGs(getOnlyCmd(inp))==true) ) { return true; }
            return false;
        }

        // cmd : loadfile -console OR loadfile -file <filename> special command to load commmand set from file
        if (getOnlyCmd(inp)=="loadfile")
        {
            if (getOnlyFlag(inp)=="-console") { return true; }else
            {
                // loadfile -file <something> so valid.
                if ( (getOnlyFlag(inp)=="-file") && (getOnlyThing(inp)!="error") ) { return true; }
            }
        }
    }
    // None of these.
    return false;
}


// CommandProcessor::readCommand()
//      reads command from the console and returns it for use elsewhere without qualifying it.
std::string CommandProcessor::readCommand()
{
    // Warzone command prompt
    std::string input;
    std::string updatestate;
    std::cout<<"WarZone ["<<G_GameState<<"] > ";
    getline(std::cin, input);

    // Special Commands handled here

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // if the input is "loadcmd -file <something.txt> then load the commands from the file
    if ( (getOnlyCmd(input)=="loadcmd") && (getOnlyFlag(input)=="-file"))
    {
        std::string filename = getOnlyThing(input);            // filename = "something.txt"

        FileCommandProcessorAdapter fCPA;

        std::cout<<"Stream Test FCPA : "<< fCPA << std::endl;

        std::string currentS = G_GameState.c_str();

        fCPA.readCommand(filename, currentS);
    }

    // this manually changes G_GameState, the games gamestate so we can change "assignreinforcement" to "win" to test quit/replay cases.
    if (input=="changestate")
    {
        std::cout<<"Change state to what? > ";
        getline(std::cin, updatestate);
        if (updatestate=="start") { G_GameState = "start"; }
        if (updatestate=="maploaded") { G_GameState = "maploaded"; }
        if (updatestate=="mapvalidated") { G_GameState = "mapvalidated"; }
        if (updatestate=="playersadded") { G_GameState = "playersadded"; }
        if (updatestate=="assignreinforcement") { G_GameState = "assignreinforement"; }
        if (updatestate=="win") { G_GameState = "win"; }
        if (updatestate=="exit program") { G_GameState = "exit program"; }
    }

    // You can only quit when you're ahead.
    if ( (input=="quit") && (G_GameState=="win") )
    {
        G_GameState="exit program";
        std::cout<<"Exiting Warzone. Goodbye."<<std::endl;
        exit(1);
    }

    // For all others : Return raw input from prompt after special cases considered.
    return input;
};

// saveCommand()
//      runs private readCommand() to get commands from prompt, checks if valid, if so, create
//      the command and add it to the private vector.
void CommandProcessor::saveCommand()
{
    std::string input = readCommand();

    // new Command(cmd, flag, filename, gamestate)
    if (validate(input)==true)
    {
        // The command is valid, create it and add it to the private vector<Command*> listCmd

        // std::cout<<"Command created and added to back of listCmd : "<<input<<std::endl;
        Command* valid_command = new Command(getOnlyCmd(input), getOnlyFlag(input), getOnlyThing(input), G_GameState);
        listCmd.push_back(valid_command);
        Notify(this);
    }else
    {
        std::cout<< input << "not a valid command."<<std::endl;
    }
}

// getCommand()
//      returns current command at front of cmdList
Command* CommandProcessor::getCommand()
{
    if (!listCmd.empty()) {
        Command *next_cmd = listCmd.back();
        return next_cmd;
    };
    return new Command("error","error","error","error");
}

///////////////////////////////////////////////////////////////

// FILECOMMANDPROCESSINGADAPTER CLASS /////////////////////////

// Default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
}

// Copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& aFCPA)
{
    // Copy over the one attribute
    listC = aFCPA.listC;
}

// Copy constructor
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator = (const FileCommandProcessorAdapter& aFCPA)                     // Assignment Operator
{
    if (this == &aFCPA) { return *this; }
    listC = aFCPA.listC;    // Copy the list of acmdP into listCmd of this object
    return *this;
}

// Stream operator
std::ostream& operator<<(std::ostream& stream, const FileCommandProcessorAdapter& aFCPA)
{
    if (aFCPA.listC.size()!=0)
    {
        stream << "        List of valid issued commands : ";
        for (int i = 0; i < aFCPA.listC.size(); i++) {
            std::string cmd = aFCPA.listC.at(i)->getCmd();
            stream << "-----------------[" << i << "] " << cmd;
        }
        stream << "\b\b";
    }else
    {
        std::cout<<"No commands in list."<<std::endl;
    }
    return stream;
}


// string next_updateGs(string cmd, string existingstate)
//       for the existing state and file-loaded command, see if this is valid
//       given the sequence of file loaded commands. If so, transition and return updated state.
//       different from the one in CommandProcessor because we need to consider "potential"
//       subsequent states before loading.
std::string FileCommandProcessorAdapter::next_updateGs(std::string cmd, std::string existingstate)
{
    if (existingstate=="start" && cmd=="loadmap") { return "maploaded";  }

    if (existingstate=="maploaded" && cmd=="loadmap") { return "maploaded";  }
    if (existingstate=="maploaded" && cmd=="validatemap") { return "mapvalidated";  }

    if (existingstate=="mapvalidated" && cmd=="addplayer") { return "playersadded";  }
    if (existingstate=="playersadded" && cmd=="addplayer") { return "playersadded";  }

    if (existingstate=="win" && cmd=="replay") { return "start";  }
    if (existingstate=="win" && cmd=="quit") { return "exit program";  }

    return "error";
}

// void readCommand(string filename, string state)
//      this reads the commands in from the file (not the console) and saves them
//      in vector<Command*> listC. runcmd will run this list of commands (if prompted)
void FileCommandProcessorAdapter::readCommand(std::string filename, std::string init_Gs)
{
    // Read cmd line by line into listCmd vector IF VALID for gamestate/syntax
    std::string line;
    std::string full_fn = "C:\\Users\\CHARLIE\\CLionProjects\\A2_345_v2\\"+filename;
    std::string gSchange(init_Gs);

    std::ifstream file(full_fn);
    int count=0;

    if (file.is_open())
    {
        std::cout<<" "<<filename<<" loaded "<<std::endl;
        while (getline(file, line))
        {
            std::string projected_next_state = next_updateGs(getOnlyCmd(line), gSchange);

            //std::cout<<"........["<<count<<"] :  "<< line << " projected state :  "<< projected_next_state<<"  current state : "<< gSchange <<std::endl;

            if (validate(line) && projected_next_state != "error")
            {
                // Command is valid. Create a command and push to FCPA's own cmdline vector.
                Command* valid_command = new Command(getOnlyCmd(line), getOnlyFlag(line), getOnlyThing(line), gSchange);
                std::cout<<"..................loading valid command [ "<<line<<" ] from file"<<std::endl;
                listC.push_back(valid_command);
                //std::cout<<"New valid command created for "<<line<<" and saved to listCmd "<<std::endl;

                // The potential next state is updated, then subsequent commands are dependant on it.
                gSchange = projected_next_state;
            }
            count++;
        }
        // std::cout<<" size of listC is " << listC.size() << std::endl;
        file.close();
    }else{ std::cout<<" Error : Unable to open "<<filename<<"."<<std::endl; }  //Error message if file doesn't open
}
///////////////////////////////////////////////////////////////



