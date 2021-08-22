//
//  SelectionViewController.h
//
//  Created by Кондакова Татьяна Андреевна on 26.04.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SelectionViewController : UIViewController  {
	CFRunLoopRef currentLoop;
	int ret;
	NSMutableArray *selectionArray;
	IBOutlet UITableView *table;
	int rowsNumber;
	int baseRowNumber;
	int needScroll;
}

@property int ret;
@property CFRunLoopRef currentLoop;
@property (nonatomic, strong) NSMutableArray *selectionArray;

-(size_t) rowToItemNumber: (int) row;
@end
