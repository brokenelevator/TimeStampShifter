========================================================================
    TimeStampShifter by Aleksander Lorenc
========================================================================

Program can batch shift timestamps in files.
This program was written using Notepad++ and compiled using MinGW32.
Idea to write this program came when I needed to correct timestamps from a camera with wrong date.
I calculated the difference between camera time and current time and used TimeStampCreator to set the correct the timestamp.
The problem was that I had to manually calculate correct time(add the difference) for every timestamp.
I figured it would be much easier if I could just say 'shift forward in time by 12 weeks'.
Which is why I added a third member to TimeStamp* family.
Thanks to MSDN Library I was able to code what I needed.

/////////////////////////////////////////////////////////////////////////////
Usage:

tss [target] [creation] [access] [write] [direction] [weeks] [days] [hours] [minutes] [seconds]

target - file to save timestamp[s] to
creation, access, write - timestamp options:
	c - replace the timestamp
	x - leave unchanged
direction:
	+(plus) shift forwards(towards the future)
	-(minus) shift backwards(towards the past)
weeks, days, hours, minutes, seconds - amount of time to shift

Any time you write bad command information about usage is shown.

Examples:
If you want to shift creation date of a.txt file 20 weeks into future you'll write the following
tss a.txt c x x + 20 0 0 0 0
If want to shift last access timestamp and last save timestamp of b.txt 2 days and 20 seconds towards the past you'll write the following
tss b.txt x c c - 0 2 0 0 20

/////////////////////////////////////////////////////////////////////////////
Requirments:

Windows 2000 Professional or above

/////////////////////////////////////////////////////////////////////////////
Other information:

The filenames I was using were non-latin(hangul) and the program failed. This is what I've done to make it work. There might be an easier/better way.
I made a utf-8 without bom batch(.bat) file in Notepad++. First line was "chcp 65001". Then "tsm..."
Then I run it through PowerShell ISE v2. There is command line in lower half. I wrote "./file.bat".

/////////////////////////////////////////////////////////////////////////////
