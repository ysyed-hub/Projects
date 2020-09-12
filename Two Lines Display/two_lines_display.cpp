//
//  main.cpp
//  two_lines_display
//
//  Created by Yunus Syed on 9/9/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class LongText {
    string long_text;
    
public:
    LongText(string text) : long_text(text) {};
    void DisplayText ();
    
};

void LongText::DisplayText () {
    int newline_counter = 2;
    for (int i = 0; i < long_text.length(); i++) {
        char c = long_text[i];
        if (c != '\n') {
            cout << c;
            continue;
        }
        newline_counter--;
        if (newline_counter == 0) {
            newline_counter = 2;
            cout << "(Press <enter> to continue)";
            cin.ignore();
            continue;
        }
        cout << c;
    }
}



int main(int argc, const char * argv[]) {
    
    LongText sample_text("Lately, I’ve been noticing how my sentences have a tendency to keep going when I write them onscreen. \nThis goes for concentrated writing as well as correspondence. \n(Twain probably believed that correspondence, in an ideal world, also demands concentration. But he never used email.) \n Last week I caught myself packing four conjunctions into a three-line sentence in an email.\n That’s inexcusable. Since then, I have tried to eschew conjunctions whenever possible.\n Gone are the commas, the and’s, but’s, and so’s; in are staccato declaratives.\n Better to read like bad Hemingway than bad Faulkner. Try putting some prose onscreen, though, and they mix themselves up pretty quickly.\n This has much to do with the time constraints we claim to feel in the digital age. We don’t have time to compose letters and post them anymore–much less pay postage, what with all the banks kinda-sorta losing our money these days–so we blast a few emails. \nWe don’t have time to talk, so we text. We don’t have time to text to specific people, so we update our Facebook status. \nWe don’t have time to write essays, so we blog.");
    
    sample_text.DisplayText();
    cout << "\n";
    
    return 0;
}
