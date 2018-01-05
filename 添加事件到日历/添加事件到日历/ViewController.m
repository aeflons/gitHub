//
//  ViewController.m
//  添加事件到日历
//
//  Created by yujunzhen on 2018/1/5.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#import "ViewController.h"
#import <EventKit/EventKit.h>
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    UIButton * button = [[UIButton alloc]init];
    button.frame = CGRectMake(0, 0, 100, 40);
    button.center = CGPointMake(self.view.frame.size.width*0.5  , self.view.frame.size.height * 0.5);
    button.backgroundColor = [UIColor redColor];
    [button setTitle:@"写日历" forState:UIControlStateNormal];
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [button addTarget:self action:@selector(saveEvent:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
}
-(void)saveEvent:(id)sender
{
    EKEventStore *eventStore = [[EKEventStore alloc] init];

    if ([eventStore respondsToSelector:@selector(requestAccessToEntityType:completion:)]) {
        [eventStore requestAccessToEntityType:EKEntityTypeEvent completion:^(BOOL granted, NSError * _Nullable error) {
            if (error) {
                NSLog(@"error == %@",error);
            }
            else if (!granted){
                NSLog(@"用户拒绝");
            }else{
                EKEvent *event = [EKEvent eventWithEventStore:eventStore];
                NSLog(@"%@",event);
                event.title = @"234";
                event.location = @"深圳";
                NSDateFormatter *tempFormatter = [[NSDateFormatter alloc]init];
                [tempFormatter setDateFormat:@"dd.MM.yyyy HH:mm"];
                
                event.startDate = [[NSDate alloc]init ];
                event.endDate   = [[NSDate alloc]init ];
                event.allDay = YES;
                
                //添加提醒
                [event addAlarm:[EKAlarm alarmWithRelativeOffset:60.0f * +60.0f * 24]];
                [event addAlarm:[EKAlarm alarmWithRelativeOffset:60.0f * -15.0f]];
                
                [event setCalendar:[eventStore defaultCalendarForNewEvents]];
                NSError *err;
                [eventStore saveEvent:event span:EKSpanThisEvent error:&err];
                dispatch_async(dispatch_get_main_queue(), ^{
                    
               
                UIAlertView *alert = [[UIAlertView alloc]
                                      initWithTitle:@"Event Created"
                                      message:@"Yay!?"
                                      delegate:nil
                                      cancelButtonTitle:@"Okay"
                                      otherButtonTitles:nil];
                [alert show];
                
                NSLog(@"保存成功");
                     });
            }
        }];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
