#include "dialogue.hpp"

#if __APPLE__
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#endif

std::string dialogueInput(const char* prompt, const char* defaultText){
#if __APPLE__
    // Convert type
    NSString *nsPrompt = [NSString stringWithCString:prompt
                                       encoding:[NSString defaultCStringEncoding]];
    NSString *nsDefaultText = [NSString stringWithCString:defaultText
                                       encoding:[NSString defaultCStringEncoding]];
    // Alert dialogue
    NSAlert *alert = [NSAlert alertWithMessageText: nsPrompt
                                        defaultButton:@"OK"
                                      alternateButton:@"Cancel"
                                          otherButton:nil
                            informativeTextWithFormat:@""];
    // Edit box
   NSTextField *inputBox = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 0, 200, 24)];
    
   [inputBox setStringValue:nsDefaultText];
   [inputBox autorelease];

    // Add edit box to alert dialogue
   [alert setAccessoryView:inputBox];
    // Button
   NSInteger button = [alert runModal];
   if (button == NSAlertDefaultReturn) {
       [inputBox validateEditing];
       return [[inputBox stringValue] UTF8String];
   } else if (button == NSAlertAlternateReturn) {
       return nil;
   } else {
       return nil;
   }
#else
    return nullptr;
#endif
}

