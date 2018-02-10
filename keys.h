#ifndef KEYS
#define KEYS

#include <map>
#include <string>
#include <array>
#include <ctime>
#include <vector>
#include <algorithm>

/*
0-26, 28-31, 127 are unused (irrelevant chars)
keys is a map that follows the given structure
	keys[KEY NAME] = array(
		[0] => PRESSED, 1 for pressed, 0 for unpressed
		[1] => mouseX inital press,
		[2] => mouseY inital press,
		[3] => mouseX release,
		[4] => mouseY release,
		[5] => time pressed
	)
*/
std::map<std::string, std::array<int, 6>> keys;

/*
	Keeps track of all keys that are pressed
*/
std::vector<std::string> pressedKeys;

//Initializes all the keys
//This front loads all the work on startup, uses potentially more memory then required
void initKeys() {
	//27
	keys["ESCAPE"][0] = 0;
	keys["ESCAPE"][1] = 0;
	keys["ESCAPE"][2] = 0;
	keys["ESCAPE"][3] = 0;
	keys["ESCAPE"][4] = 0;
	keys["ESCAPE"][5] = 0;
	//32
	keys["SPACE"][0] = 0;
	keys["SPACE"][1] = 0;
	keys["SPACE"][2] = 0;
	keys["SPACE"][3] = 0;
	keys["SPACE"][5] = 0;
	//33
	keys["EXCLAMATION MARK"][0] = 0;
	keys["EXCLAMATION MARK"][1] = 0;
	keys["EXCLAMATION MARK"][2] = 0;
	keys["EXCLAMATION MARK"][3] = 0;
	keys["EXCLAMATION MARK"][4] = 0;
	keys["EXCLAMATION MARK"][5] = 0;
	//34
	keys["DOUBLE QUOTE"][0] = 0;
	keys["DOUBLE QUOTE"][1] = 0;
	keys["DOUBLE QUOTE"][2] = 0;
	keys["DOUBLE QUOTE"][3] = 0;
	keys["DOUBLE QUOTE"][4] = 0;
	keys["DOUBLE QUOTE"][5] = 0;
	//35
	keys["HASH"][0] = 0;
	keys["HASH"][1] = 0;
	keys["HASH"][2] = 0;
	keys["HASH"][3] = 0;
	keys["HASH"][4] = 0;
	keys["HASH"][5] = 0;
	//36
	keys["DOLLAR"][0] = 0;
	keys["DOLLAR"][1] = 0;
	keys["DOLLAR"][2] = 0;
	keys["DOLLAR"][3] = 0;
	keys["DOLLAR"][4] = 0;
	keys["DOLLAR"][5] = 0;
	//37
	keys["PERCENT"][0] = 0;
	keys["PERCENT"][1] = 0;
	keys["PERCENT"][2] = 0;
	keys["PERCENT"][3] = 0;
	keys["PERCENT"][4] = 0;
	keys["PERCENT"][5] = 0;
	//38
	keys["AMPERSAND"][0] = 0;
	keys["AMPERSAND"][1] = 0;
	keys["AMPERSAND"][2] = 0;
	keys["AMPERSAND"][3] = 0;
	keys["AMPERSAND"][4] = 0;
	keys["AMPERSAND"][5] = 0;
	//39
	keys["SINGLE QUOTE"][0] = 0;
	keys["SINGLE QUOTE"][1] = 0;
	keys["SINGLE QUOTE"][2] = 0;
	keys["SINGLE QUOTE"][3] = 0;
	keys["SINGLE QUOTE"][4] = 0;
	keys["SINGLE QUOTE"][5] = 0;
	//40
	keys["LEFT PARENTHESIS"][0] = 0;
	keys["LEFT PARENTHESIS"][1] = 0;
	keys["LEFT PARENTHESIS"][2] = 0;
	keys["LEFT PARENTHESIS"][3] = 0;
	keys["LEFT PARENTHESIS"][4] = 0;
	keys["LEFT PARENTHESIS"][5] = 0;
	//41
	keys["RIGHT PARENTHESIS"][0] = 0;
	keys["RIGHT PARENTHESIS"][1] = 0;
	keys["RIGHT PARENTHESIS"][2] = 0;
	keys["RIGHT PARENTHESIS"][3] = 0;
	keys["RIGHT PARENTHESIS"][4] = 0;
	keys["RIGHT PARENTHESIS"][5] = 0;
	//42
	keys["ASTERISK"][0] = 0;
	keys["ASTERISK"][1] = 0;
	keys["ASTERISK"][2] = 0;
	keys["ASTERISK"][3] = 0;
	keys["ASTERISK"][4] = 0;
	keys["ASTERISK"][5] = 0;
	//43
	keys["PLUS"][0] = 0;
	keys["PLUS"][1] = 0;
	keys["PLUS"][2] = 0;
	keys["PLUS"][3] = 0;
	keys["PLUS"][4] = 0;
	keys["PLUS"][5] = 0;
	//44
	keys["COMMA"][0] = 0;
	keys["COMMA"][1] = 0;
	keys["COMMA"][2] = 0;
	keys["COMMA"][3] = 0;
	keys["COMMA"][4] = 0;
	keys["COMMA"][5] = 0;
	//45
	keys["HYPHEN"][0] = 0;
	keys["HYPHEN"][1] = 0;
	keys["HYPHEN"][2] = 0;
	keys["HYPHEN"][3] = 0;
	keys["HYPHEN"][4] = 0;
	keys["HYPHEN"][5] = 0;
	//46
	keys["PERIOD"][0] = 0;
	keys["PERIOD"][1] = 0;
	keys["PERIOD"][2] = 0;
	keys["PERIOD"][3] = 0;
	keys["PERIOD"][4] = 0;
	keys["PERIOD"][5] = 0;
	//47
	keys["FORWARD SLASH"][0] = 0;
	keys["FORWARD SLASH"][1] = 0;
	keys["FORWARD SLASH"][2] = 0;
	keys["FORWARD SLASH"][3] = 0;
	keys["FORWARD SLASH"][4] = 0;
	keys["FORWARD SLASH"][5] = 0;
	//48
	keys["ZERO"][0] = 0;
	keys["ZERO"][1] = 0;
	keys["ZERO"][2] = 0;
	keys["ZERO"][3] = 0;
	keys["ZERO"][4] = 0;
	keys["ZERO"][5] = 0;
	//49
	keys["ONE"][0] = 0;
	keys["ONE"][1] = 0;
	keys["ONE"][2] = 0;
	keys["ONE"][3] = 0;
	keys["ONE"][4] = 0;
	keys["ONE"][5] = 0;
	//50
	keys["TWO"][0] = 0;
	keys["TWO"][1] = 0;
	keys["TWO"][2] = 0;
	keys["TWO"][3] = 0;
	keys["TWO"][4] = 0;
	keys["TWO"][5] = 0;
	//51
	keys["THREE"][0] = 0;
	keys["THREE"][1] = 0;
	keys["THREE"][2] = 0;
	keys["THREE"][3] = 0;
	keys["THREE"][3] = 0;
	keys["THREE"][4] = 0;
	//52
	keys["FOUR"][0] = 0;
	keys["FOUR"][1] = 0;
	keys["FOUR"][2] = 0;
	keys["FOUR"][3] = 0;
	keys["FOUR"][4] = 0;
	keys["FOUR"][5] = 0;
	//53
	keys["FIVE"][0] = 0;
	keys["FIVE"][1] = 0;
	keys["FIVE"][2] = 0;
	keys["FIVE"][3] = 0;
	keys["FIVE"][4] = 0;
	keys["FIVE"][5] = 0;
	//54
	keys["SIX"][0] = 0;
	keys["SIX"][1] = 0;
	keys["SIX"][2] = 0;
	keys["SIX"][3] = 0;
	keys["SIX"][4] = 0;
	keys["SIX"][5] = 0;
	//55
	keys["SEVEN"][0] = 0;
	keys["SEVEN"][1] = 0;
	keys["SEVEN"][2] = 0;
	keys["SEVEN"][3] = 0;
	keys["SEVEN"][4] = 0;
	keys["SEVEN"][5] = 0;
	//56
	keys["EIGHT"][0] = 0;
	keys["EIGHT"][1] = 0;
	keys["EIGHT"][2] = 0;
	keys["EIGHT"][3] = 0;
	keys["EIGHT"][4] = 0;
	keys["EIGHT"][5] = 0;
	//57
	keys["NINE"][0] = 0;
	keys["NINE"][1] = 0;
	keys["NINE"][2] = 0;
	keys["NINE"][3] = 0;
	keys["NINE"][4] = 0;
	keys["NINE"][5] = 0;
	//58
	keys["COLON"][0] = 0;
	keys["COLON"][1] = 0;
	keys["COLON"][2] = 0;
	keys["COLON"][3] = 0;
	keys["COLON"][4] = 0;
	keys["COLON"][5] = 0;
	//59
	keys["SEMICOLON"][0] = 0;
	keys["SEMICOLON"][1] = 0;
	keys["SEMICOLON"][2] = 0;
	keys["SEMICOLON"][3] = 0;
	keys["SEMICOLON"][4] = 0;
	keys["SEMICOLON"][5] = 0;
	//60
	keys["LESS THAN"][0] = 0;
	keys["LESS THAN"][1] = 0;
	keys["LESS THAN"][2] = 0;
	keys["LESS THAN"][3] = 0;
	keys["LESS THAN"][4] = 0;
	keys["LESS THAN"][5] = 0;
	//61
	keys["EQUAL"][0] = 0;
	keys["EQUAL"][1] = 0;
	keys["EQUAL"][2] = 0;
	keys["EQUAL"][3] = 0;
	keys["EQUAL"][4] = 0;
	keys["EQUAL"][5] = 0;
	//62
	keys["GREATER THAN"][0] = 0;
	keys["GREATER THAN"][1] = 0;
	keys["GREATER THAN"][2] = 0;
	keys["GREATER THAN"][3] = 0;
	keys["GREATER THAN"][4] = 0;
	keys["GREATER THAN"][5] = 0;
	//63
	keys["QUESTION MARK"][0] = 0;
	keys["QUESTION MARK"][1] = 0;
	keys["QUESTION MARK"][2] = 0;
	keys["QUESTION MARK"][3] = 0;
	keys["QUESTION MARK"][4] = 0;
	keys["QUESTION MARK"][5] = 0;
	//64
	keys["AT"][0] = 0;
	keys["AT"][1] = 0;
	keys["AT"][2] = 0;
	keys["AT"][3] = 0;
	keys["AT"][4] = 0;
	keys["AT"][5] = 0;
	//65
	keys["A"][0] = 0;
	keys["A"][1] = 0;
	keys["A"][2] = 0;
	keys["A"][3] = 0;
	keys["A"][4] = 0;
	keys["A"][5] = 0;
	//66
	keys["B"][0] = 0;
	keys["B"][1] = 0;
	keys["B"][2] = 0;
	keys["B"][3] = 0;
	keys["B"][4] = 0;
	keys["B"][5] = 0;
	//67
	keys["C"][0] = 0;
	keys["C"][1] = 0;
	keys["C"][2] = 0;
	keys["C"][3] = 0;
	keys["C"][4] = 0;
	keys["C"][5] = 0;
	//68
	keys["D"][0] = 0;
	keys["D"][1] = 0;
	keys["D"][2] = 0;
	keys["D"][3] = 0;
	keys["D"][4] = 0;
	keys["D"][5] = 0;
	//69
	keys["E"][0] = 0;
	keys["E"][1] = 0;
	keys["E"][2] = 0;
	keys["E"][3] = 0;
	keys["E"][4] = 0;
	keys["E"][5] = 0;
	//70
	keys["F"][0] = 0;
	keys["F"][1] = 0;
	keys["F"][2] = 0;
	keys["F"][3] = 0;
	keys["F"][4] = 0;
	keys["F"][5] = 0;
	//71
	keys["G"][0] = 0;
	keys["G"][1] = 0;
	keys["G"][2] = 0;
	keys["G"][3] = 0;
	keys["G"][4] = 0;
	keys["G"][5] = 0;
	//72
	keys["H"][0] = 0;
	keys["H"][1] = 0;
	keys["H"][2] = 0;
	keys["H"][3] = 0;
	keys["H"][4] = 0;
	keys["H"][5] = 0;
	//73
	keys["I"][0] = 0;
	keys["I"][1] = 0;
	keys["I"][2] = 0;
	keys["I"][3] = 0;
	keys["I"][4] = 0;
	keys["I"][5] = 0;
	//74
	keys["J"][0] = 0;
	keys["J"][1] = 0;
	keys["J"][2] = 0;
	keys["J"][3] = 0;
	keys["J"][4] = 0;
	keys["J"][5] = 0;
	//75
	keys["K"][0] = 0;
	keys["K"][1] = 0;
	keys["K"][2] = 0;
	keys["K"][3] = 0;
	keys["K"][4] = 0;
	keys["K"][5] = 0;
	//76
	keys["L"][0] = 0;
	keys["L"][1] = 0;
	keys["L"][2] = 0;
	keys["L"][3] = 0;
	keys["L"][4] = 0;
	keys["L"][5] = 0;
	//77
	keys["M"][0] = 0;
	keys["M"][1] = 0;
	keys["M"][2] = 0;
	keys["M"][3] = 0;
	keys["M"][4] = 0;
	keys["M"][5] = 0;
	//78
	keys["N"][0] = 0;
	keys["N"][1] = 0;
	keys["N"][2] = 0;
	keys["N"][3] = 0;
	keys["N"][4] = 0;
	keys["N"][5] = 0;
	//79
	keys["O"][0] = 0;
	keys["O"][1] = 0;
	keys["O"][2] = 0;
	keys["O"][3] = 0;
	keys["O"][4] = 0;
	keys["O"][5] = 0;
	//80
	keys["P"][0] = 0;
	keys["P"][1] = 0;
	keys["P"][2] = 0;
	keys["P"][3] = 0;
	keys["P"][4] = 0;
	keys["P"][5] = 0;
	//81
	keys["Q"][0] = 0;
	keys["Q"][1] = 0;
	keys["Q"][2] = 0;
	keys["Q"][3] = 0;
	keys["Q"][4] = 0;
	keys["Q"][5] = 0;
	//82
	keys["R"][0] = 0;
	keys["R"][1] = 0;
	keys["R"][2] = 0;
	keys["R"][3] = 0;
	keys["R"][4] = 0;
	keys["R"][5] = 0;
	//83
	keys["S"][0] = 0;
	keys["S"][1] = 0;
	keys["S"][2] = 0;
	keys["S"][3] = 0;
	keys["S"][4] = 0;
	keys["S"][5] = 0;
	//84
	keys["T"][0] = 0;
	keys["T"][1] = 0;
	keys["T"][2] = 0;
	keys["T"][3] = 0;
	keys["T"][4] = 0;
	keys["T"][5] = 0;
	//85
	keys["U"][0] = 0;
	keys["U"][1] = 0;
	keys["U"][2] = 0;
	keys["U"][3] = 0;
	keys["U"][4] = 0;
	keys["U"][5] = 0;
	//86
	keys["V"][0] = 0;
	keys["V"][1] = 0;
	keys["V"][2] = 0;
	keys["V"][3] = 0;
	keys["V"][4] = 0;
	keys["V"][5] = 0;
	//87
	keys["W"][0] = 0;
	keys["W"][1] = 0;
	keys["W"][2] = 0;
	keys["W"][3] = 0;
	keys["W"][4] = 0;
	keys["W"][5] = 0;
	//88
	keys["X"][0] = 0;
	keys["X"][1] = 0;
	keys["X"][2] = 0;
	keys["X"][3] = 0;
	keys["X"][4] = 0;
	keys["X"][5] = 0;
	//89
	keys["Y"][0] = 0;
	keys["Y"][1] = 0;
	keys["Y"][2] = 0;
	keys["Y"][3] = 0;
	keys["Y"][4] = 0;
	keys["Y"][5] = 0;
	//90
	keys["Z"][0] = 0;
	keys["Z"][1] = 0;
	keys["Z"][2] = 0;
	keys["Z"][3] = 0;
	keys["Z"][4] = 0;
	keys["Z"][5] = 0;
	//91
	keys["LEFT BRACKET"][0] = 0;
	keys["LEFT BRACKET"][1] = 0;
	keys["LEFT BRACKET"][2] = 0;
	keys["LEFT BRACKET"][3] = 0;
	keys["LEFT BRACKET"][4] = 0;
	keys["LEFT BRACKET"][5] = 0;
	//92
	keys["BACKSLASH"][0] = 0;
	keys["BACKSLASH"][1] = 0;
	keys["BACKSLASH"][2] = 0;
	keys["BACKSLASH"][3] = 0;
	keys["BACKSLASH"][4] = 0;
	keys["BACKSLASH"][5] = 0;
	//93
	keys["RIGHT BRACKET"][0] = 0;
	keys["RIGHT BRACKET"][1] = 0;
	keys["RIGHT BRACKET"][2] = 0;
	keys["RIGHT BRACKET"][3] = 0;
	keys["RIGHT BRACKET"][4] = 0;
	keys["RIGHT BRACKET"][5] = 0;
	//94
	keys["CARET"][0] = 0;
	keys["CARET"][1] = 0;
	keys["CARET"][2] = 0;
	keys["CARET"][3] = 0;
	keys["CARET"][4] = 0;
	keys["CARET"][5] = 0;
	//95
	keys["UNDERSCORE"][0] = 0;
	keys["UNDERSCORE"][1] = 0;
	keys["UNDERSCORE"][2] = 0;
	keys["UNDERSCORE"][3] = 0;
	keys["UNDERSCORE"][4] = 0;
	keys["UNDERSCORE"][5] = 0;
	//96
	keys["BACK TICK"][0] = 0;
	keys["BACK TICK"][1] = 0;
	keys["BACK TICK"][2] = 0;
	keys["BACK TICK"][3] = 0;
	keys["BACK TICK"][4] = 0;
	keys["BACK TICK"][5] = 0;
	//97
	keys["a"][0] = 0;
	keys["a"][1] = 0;
	keys["a"][2] = 0;
	keys["a"][3] = 0;
	keys["a"][4] = 0;
	keys["a"][5] = 0;
	//98
	keys["b"][0] = 0;
	keys["b"][1] = 0;
	keys["b"][2] = 0;
	keys["b"][3] = 0;
	keys["b"][4] = 0;
	keys["b"][5] = 0;
	//99
	keys["c"][0] = 0;
	keys["c"][1] = 0;
	keys["c"][2] = 0;
	keys["c"][3] = 0;
	keys["c"][4] = 0;
	keys["c"][5] = 0;
	//100
	keys["d"][0] = 0;
	keys["d"][1] = 0;
	keys["d"][2] = 0;
	keys["d"][3] = 0;
	keys["d"][4] = 0;
	keys["d"][5] = 0;
	//101
	keys["e"][0] = 0;
	keys["e"][1] = 0;
	keys["e"][2] = 0;
	keys["e"][3] = 0;
	keys["e"][4] = 0;
	keys["e"][5] = 0;
	//102
	keys["f"][0] = 0;
	keys["f"][1] = 0;
	keys["f"][2] = 0;
	keys["f"][3] = 0;
	keys["f"][4] = 0;
	keys["f"][5] = 0;
	//103
	keys["g"][0] = 0;
	keys["g"][1] = 0;
	keys["g"][2] = 0;
	keys["g"][3] = 0;
	keys["g"][4] = 0;
	keys["g"][5] = 0;
	//104
	keys["h"][0] = 0;
	keys["h"][1] = 0;
	keys["h"][2] = 0;
	keys["h"][3] = 0;
	keys["h"][4] = 0;
	keys["h"][5] = 0;
	//105
	keys["i"][0] = 0;
	keys["i"][1] = 0;
	keys["i"][2] = 0;
	keys["i"][3] = 0;
	keys["i"][4] = 0;
	keys["i"][5] = 0;
	//106
	keys["j"][0] = 0;
	keys["j"][1] = 0;
	keys["j"][2] = 0;
	keys["j"][3] = 0;
	keys["j"][4] = 0;
	keys["j"][5] = 0;
	//107
	keys["k"][0] = 0;
	keys["k"][1] = 0;
	keys["k"][2] = 0;
	keys["k"][3] = 0;
	keys["k"][4] = 0;
	keys["k"][5] = 0;
	//108
	keys["l"][0] = 0;
	keys["l"][1] = 0;
	keys["l"][2] = 0;
	keys["l"][3] = 0;
	keys["l"][4] = 0;
	keys["l"][5] = 0;
	//109
	keys["m"][0] = 0;
	keys["m"][1] = 0;
	keys["m"][2] = 0;
	keys["m"][3] = 0;
	keys["m"][4] = 0;
	keys["m"][5] = 0;
	//110
	keys["n"][0] = 0;
	keys["n"][1] = 0;
	keys["n"][2] = 0;
	keys["n"][3] = 0;
	keys["n"][4] = 0;
	keys["n"][5] = 0;
	//111
	keys["o"][0] = 0;
	keys["o"][1] = 0;
	keys["o"][2] = 0;
	keys["o"][3] = 0;
	keys["o"][4] = 0;
	keys["o"][5] = 0;
	//112
	keys["p"][0] = 0;
	keys["p"][1] = 0;
	keys["p"][2] = 0;
	keys["p"][3] = 0;
	keys["p"][4] = 0;
	keys["p"][5] = 0;
	//113
	keys["q"][0] = 0;
	keys["q"][1] = 0;
	keys["q"][2] = 0;
	keys["q"][3] = 0;
	keys["q"][4] = 0;
	keys["q"][5] = 0;
	//114
	keys["r"][0] = 0;
	keys["r"][1] = 0;
	keys["r"][2] = 0;
	keys["r"][3] = 0;
	keys["r"][4] = 0;
	keys["r"][5] = 0;
	//115
	keys["s"][0] = 0;
	keys["s"][1] = 0;
	keys["s"][2] = 0;
	keys["s"][3] = 0;
	keys["s"][4] = 0;
	keys["s"][5] = 0;
	//116
	keys["t"][0] = 0;
	keys["t"][1] = 0;
	keys["t"][2] = 0;
	keys["t"][3] = 0;
	keys["t"][4] = 0;
	keys["t"][5] = 0;
	//117
	keys["u"][0] = 0;
	keys["u"][1] = 0;
	keys["u"][2] = 0;
	keys["u"][3] = 0;
	keys["u"][4] = 0;
	keys["u"][5] = 0;
	//118
	keys["v"][0] = 0;
	keys["v"][1] = 0;
	keys["v"][2] = 0;
	keys["v"][3] = 0;
	keys["v"][4] = 0;
	keys["v"][5] = 0;
	//119
	keys["w"][0] = 0;
	keys["w"][1] = 0;
	keys["w"][2] = 0;
	keys["w"][3] = 0;
	keys["w"][4] = 0;
	keys["w"][5] = 0;
	//120
	keys["x"][0] = 0;
	keys["x"][1] = 0;
	keys["x"][2] = 0;
	keys["x"][3] = 0;
	keys["x"][4] = 0;
	keys["x"][5] = 0;
	//121
	keys["y"][0] = 0;
	keys["y"][1] = 0;
	keys["y"][2] = 0;
	keys["y"][3] = 0;
	keys["y"][4] = 0;
	keys["y"][5] = 0;
	//122
	keys["z"][0] = 0;
	keys["z"][1] = 0;
	keys["z"][2] = 0;
	keys["z"][3] = 0;
	keys["z"][4] = 0;
	keys["z"][5] = 0;
	//123
	keys["LEFT BRACE"][0] = 0;
	keys["LEFT BRACE"][1] = 0;
	keys["LEFT BRACE"][2] = 0;
	keys["LEFT BRACE"][3] = 0;
	keys["LEFT BRACE"][4] = 0;
	keys["LEFT BRACE"][5] = 0;
	//124
	keys["OR"][0] = 0;
	keys["OR"][1] = 0;
	keys["OR"][2] = 0;
	keys["OR"][3] = 0;
	keys["OR"][4] = 0;
	keys["OR"][5] = 0;
	//125
	keys["RIGHT BRACE"][0] = 0;
	keys["RIGHT BRACE"][1] = 0;
	keys["RIGHT BRACE"][2] = 0;
	keys["RIGHT BRACE"][3] = 0;
	keys["RIGHT BRACE"][4] = 0;
	keys["RIGHT BRACE"][5] = 0;
	//126
	keys["TILDE"][0] = 0;
	keys["TILDE"][1] = 0;
	keys["TILDE"][2] = 0;
	keys["TILDE"][3] = 0;
	keys["TILDE"][4] = 0;
	keys["TILDE"][5] = 0;
}

std::string getKeyFromASCII(int code) {
	switch (code) {
		case 27:
			return "ESCAPE";
		case 32:
			return "SPACE";
		case 33:
			return "EXCLAMATION MARK";
		case 34:
			return "DOUBLE QUOTE";
		case 35:
			return "HASH";
		case 36:
			return "DOLLAR";
		case 37:
			return "PERCENT";
		case 38:
			return "AMPERSAND";
		case 39:
			return "SINGLE QUOTE";
		case 40:
			return "LEFT PARENTHESIS";
		case 41:
			return "RIGHT PARENTHESIS";
		case 42:
			return "ASTERISK";
		case 43:
			return "KEYS";
		case 44:
			return "COMMA";
		case 45:
			return "HYPHEN";
		case 46:
			return "PERIOD";
		case 47:
			return "FORWARD SLASH";
		case 48:
			return "ZERO";
		case 49:
			return "ONE";
		case 50:
			return "TWO";
		case 51:
			return "THREE";
		case 52:
			return "FOUR";
		case 53:
			return "FIVE";
		case 54:
			return "SIX";
		case 55:
			return "SEVEN";
		case 56:
			return "EIGHT";
		case 57:
			return "NINE";
		case 58:
			return "COLON";
		case 59:
			return "SEMICOLON";
		case 60:
			return "LESS THAN";
		case 61:
			return "EQUAL";
		case 62:
			return "GREATER THAN";
		case 63:
			return "QUESTION MARK";
		case 64:
			return "AT";
		case 65:
			return "A";
		case 66:
			return "B";
		case 67:
			return "C";
		case 68:
			return "D";
		case 69:
			return "E";
		case 70:
			return "F";
		case 71:
			return "G";
		case 72:
			return "H";
		case 73:
			return "I";
		case 74:
			return "J";
		case 75:
			return "K";
		case 76:
			return "L";
		case 77:
			return "M";
		case 78:
			return "N";
		case 79:
			return "O";
		case 80:
			return "P";
		case 81:
			return "Q";
		case 82:
			return "R";
		case 83:
			return "S";
		case 84:
			return "T";
		case 85:
			return "U";
		case 86:
			return "V";
		case 87:
			return "W";
		case 88:
			return "X";
		case 89:
			return "Y";
		case 90:
			return "Z";
		case 91:
			return "LEFT BRACKET";
		case 92:
			return "BACKSLASH";
		case 93:
			return "RIGHT BRACKET";
		case 94:
			return "CARET";
		case 95:
			return "UNDERSCORE";
		case 96:
			return "BACKTICK";
		case 97:
			return "a";
		case 98:
			return "b";
		case 99:
			return "c";
		case 100:
			return "d";
		case 101:
			return "e";
		case 102:
			return "f";
		case 103:
			return "g";
		case 104:
			return "h";
		case 105:
			return "i";
		case 106:
			return "j";
		case 107:
			return "k";
		case 108:
			return "l";
		case 109:
			return "m";
		case 110:
			return "n";
		case 111:
			return "o";
		case 112:
			return "p";
		case 113:
			return "q";
		case 114:
			return "r";
		case 115:
			return "s";
		case 116:
			return "t";
		case 117:
			return "u";
		case 118:
			return "v";
		case 119:
			return "w";
		case 120:
			return "x";
		case 121:
			return "y";
		case 122:
			return "z";
		case 123:
			return "LEFT BRACE";
		case 124:
			return "OR";
		case 125:
			return "RIGHT BRACE";
		case 126:
			return "TILDE";
		default:
			return "ERROR";
			break;
	}
}

std::string handleKey(unsigned char key, int mouseX, int mouseY, bool pressed, bool special = false) {
	std::string val = "";
	val = getKeyFromASCII( key );
	//Making sure it was a valid key
	if (val != "ERROR") {
		//the key is not already pressed (multiple events are generated when a key is held down)
		if (keys[val][0] == 0 && pressed) {
			keys[val][0] = 1;
			keys[val][1] = mouseX;
			keys[val][2] = mouseY;
			keys[val][3] = -1;
			keys[val][4] = -1;
			keys[val][5] = static_cast<int>(std::time( 0 ));
			//std::cout << pressedKeys.size() << std::endl;
			pressedKeys.push_back( val );
			//std::cout << keys[val][0] << std::endl;
		}
			//The key is released
		else if (keys[val][0] == 1 && !pressed) {
			keys[val][0] = 0;
			keys[val][3] = mouseX;
			keys[val][4] = mouseY;
			keys[val][5] = static_cast<int>(std::time( 0 ) - keys[val][5]);
			unsigned int pos = static_cast<unsigned int>(std::find( pressedKeys.begin(), pressedKeys.end(), val ) -
														 pressedKeys.begin());
			if (pos < pressedKeys.size()) pressedKeys.erase( pressedKeys.begin() + pos );
		}
			//This code will fix bug above, however it would require creating a mapping between every key on the keyboard
			//with it's alternate value, which I don't want to do right now
		else if (keys[val][0] == 0 && !pressed && glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
#ifdef DEBUG
			std::cout << "Shift is causing problems again" << std::endl;
#endif
		} else return "No Action";
	} else return "No Action";
	return val;
}


#endif
