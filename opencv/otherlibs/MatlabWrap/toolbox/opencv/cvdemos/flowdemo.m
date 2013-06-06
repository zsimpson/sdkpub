function flowdemo(action,varargin);
%   OpenCV Optical Flow functions demo

global demoName;
demoName = 'OpenCV Optical Flow demo';
if nargin<1,
   action='InitializeDEMO';
end;

feval(action,varargin{:});
return;


%%%
%%%  Sub-function - InitializeDEMO
%%%

function InitializeDEMO()

global demoName;

% If demo is already running, bring it to the foreground.
h = findobj(allchild(0), 'tag', demoName);
if ~isempty(h)
   figure(h(1))
   return
end

screenD = get(0, 'ScreenDepth');
if screenD>8
   grayres=256;
else
   grayres=128;
end
 
imgSize = [320, 240];
ctrHt = 19; % controls' height

%==================================
% Set up the figure
DemoFig=figure( ...
   'Name',demoName, ...
   'NumberTitle','off', 'HandleVisibility', 'on', ...
   'tag', demoName, ...
   'Visible','off', 'Resize', 'off',...
   'BusyAction','Queue','Interruptible','off',...
   'IntegerHandle', 'off', ...
   'Doublebuffer', 'on', ...
   'Units', 'pixels', ...
   'Colormap', gray(grayres));

figpos = get(DemoFig, 'Position');
figpos(3) = 2.2*imgSize(1);
figpos(4) = imgSize(2) + 10*ctrHt;
set(DemoFig, 'Position', figpos);

%==================================
% Set up the image axes
row = figpos(4); col = figpos(3);
vertSpac = ctrHt;
horSpac = (col-2*imgSize(1))/3;
hSrcAx = axes('Parent', DemoFig, ...
   'units', 'pixels', ...
   'BusyAction','Queue','Interruptible','off',...
   'ydir', 'reverse', ...
   'XLim', [.5 imgSize(1)+0.5], ...
   'YLim', [.5 imgSize(2)+0.5],...
   'CLim', [0 255], ...
   'XTick',[],'YTick',[], ...
   'Position', [horSpac row-vertSpac-imgSize(2) imgSize], ...
   'UserData', []);
title('Source Image');

hDstAx = axes('Parent', DemoFig, ...
   'units', 'pixels', ...
   'BusyAction','Queue','Interruptible','off',...
   'ydir', 'reverse', ...
   'XLim', [.5 imgSize(1)+0.5], ...
   'YLim', [.5 imgSize(2)+0.5],...
   'CLim', [0 255], ...
   'XTick',[],'YTick',[], ...
   'Position', [2 * horSpac + imgSize(1) row-vertSpac-imgSize(2) imgSize], ...
   'UserData', []);
title('Destination Image');

%==================================
% Set up the images
blank = repmat(uint8(0),imgSize(2),imgSize(1));
hSrcImage = image('Parent', hSrcAx,...
   'CData', blank, ...
   'BusyAction','Queue','Interruptible','off',...
   'CDataMapping', 'scaled', ...
   'Xdata', [1 1+imgSize(1)],...
   'Ydata', [1 1+imgSize(2)],...
   'ButtonDownFcn', 'flowdemo(''GetFeatures'')', ...
   'EraseMode', 'none', ...
   'UserData', []);

hDstImage = image('Parent', hDstAx,...
   'CData', blank, ...
   'BusyAction','Queue','Interruptible','off',...
   'CDataMapping', 'scaled', ...
   'Xdata', [1 1+imgSize(1)],...
   'Ydata', [1 1+imgSize(2)],...
   'EraseMode', 'none', ...
   'UserData', []);

%====================================
% Information for all buttons (and menus)
btnWid=100;
btnHt=1.5*ctrHt;

%====================================
% The CONSOLE frame
frmBorder=0.5 * ctrHt;
dstImgPos = get(hDstAx, 'Position');

frmColor = [0.45, 0.45, 0.45];

frmWidth  = 2*frmBorder + btnWid;
frmHeight = 3*frmBorder + 2*btnHt;
frmLeft   = dstImgPos(1);
frmBottom = dstImgPos(2)-ctrHt-frmHeight;
frmPos=[frmLeft, frmBottom, ...
         frmWidth, frmHeight];
h=uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','frame', ...
   'Units','pixels', ...
   'Position',frmPos, ...
   'BackgroundColor', frmColor);

%====================================
% The Apply button
labelStr='Apply';
callbackStr='flowdemo(''Apply'')';
yPos=frmBottom+frmBorder;
applyHndl=uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','pushbutton', ...
   'Units','pixels', ...
   'Position',[frmLeft+frmBorder frmBottom+btnHt+2*frmBorder btnWid btnHt], ...
   'String',labelStr, ...
   'Enable', 'off', ...
   'Callback',callbackStr);


%====================================
% The CLOSE button
labelStr='Close';
callbackStr='close(gcf)';

closeHndl=uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','pushbutton', ...
   'Units','pixels', ...
   'Position',[frmLeft+frmBorder frmBottom+frmBorder btnWid btnHt], ...
   'Enable', 'off', ...
   'String',labelStr, ...
   'Callback',callbackStr);

c = get(DemoFig,'Color');

% Status bar
% rangePos = [64 3 280 15];
rangePos = [0 .01 1 .05];
hStatus = uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','text', ...
   'Units','normalized', ...
   'Position',rangePos, ...
   'Horiz','center', ...
   'Background',c, ...
   'Foreground',[.8 0 0], ...
   'Tag', 'Status', ...
   'String','Status bar');

srcImgPos = get(hSrcAx, 'Position');

%====================================
% The Good Features frame

frmWidth  = 2*frmBorder + btnWid;
frmHeight = 3*frmBorder + 2*btnHt;
frmLeft   = srcImgPos(1)+srcImgPos(3)-frmWidth;
frmBottom = srcImgPos(2)-ctrHt-frmHeight;
frmPos=[frmLeft, frmBottom, ...
         frmWidth, frmHeight];
h=uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','frame', ...
   'Units','pixels', ...
   'Position',frmPos, ...
   'Background', frmColor);


%====================================
% The Good Features Label
pos = [frmLeft+frmBorder, frmBottom + frmHeight - ctrHt-1, ...
       frmWidth-2*frmBorder, ctrHt];
h = uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','text', ...
   'Units','pixels', ...
   'Position',pos, ...
   'Horiz','center', ...
   'Background', frmColor, ...
   'Foreground','black', ...
   'String','Good Features');

%====================================
% The Good Features Number Label
pos = [frmLeft+frmBorder, ...
       frmBottom + frmHeight - 1*ctrHt-2*frmBorder, ...
       (frmWidth-3*frmBorder)/2, ctrHt];
h = uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','text', ...
   'Units','pixels', ...
   'Position',pos, ...
   'Horiz','right', ...
   'Background', frmColor, ...
   'Foreground','black', ...
   'String','Number: ');

%====================================
% The Good Features Number Edit
pos = [frmLeft+2*frmBorder+(frmWidth-3*frmBorder)/2, ...
       frmBottom + frmHeight - 1*ctrHt-2*frmBorder, ...
       (frmWidth-3*frmBorder)/2, ctrHt];
hNumEdit=uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','edit', ...
   'Background','white', ...
   'Foreground','black', ...
   'Units','pixels', ...
   'Position',pos, ...
   'String','20', ...
   'Horiz', 'right',...
   'Tag','AppEdit', ...
   'UserData', [20], ...
   'Callback','flowdemo(''ControlsUpdate'')');

%====================================
% The Generate button
labelStr='Generate';
callbackStr='flowdemo(''GoodFeatures'')';

genHndl=uicontrol( ...
   'Parent', DemoFig, ...
   'BusyAction','Queue','Interruptible','off',...
   'Style','pushbutton', ...
   'Units','pixels', ...
   'Position',[frmLeft+frmBorder frmBottom+frmBorder btnWid btnHt], ...
   'Enable', 'off', ...
   'String',labelStr, ...
   'Callback',callbackStr);

setstatus(DemoFig, 'Initializing Demo...');
set(DemoFig, 'Pointer', 'watch');
drawnow;
set(DemoFig, 'Visible','on');

% Put handles to graphics objects and controls in the figure's userdata
handles.SrcImage = hSrcImage;
handles.DstImage = hDstImage;

handles.SrcAx = hSrcAx;
handles.DstAx = hDstAx;

handles.NumEdit = hNumEdit;

set(DemoFig, 'UserData', handles);

LoadNewImage(DemoFig);

set(DemoFig, 'HandleVisibility','Callback')
set([closeHndl applyHndl genHndl], 'Enable', 'on');
return


%%%
%%%  Sub-Function - LoadNewImage
%%%

function LoadNewImage(DemoFig)

if nargin<1
   DemoFig = gcbf;
end

set(DemoFig,'Pointer','watch');

handles = get(DemoFig,'UserData');

hSrcImage = handles.SrcImage;
hDstImage = handles.DstImage;

rock1 = [];
rock2 = [];
load cvdemos rock1 rock2;

lkrock1 = [];
load cvdemos lkrock1;

img = rock1;
featuresA = lkrock1(1:10:200,:);
set(hSrcImage, 'Cdata', img);
set(hSrcImage, 'UserData', featuresA);

img = rock2;
set(hDstImage, 'Cdata', img);
set(hDstImage, 'UserData', []);

drawnow;

setstatus(DemoFig, 'Press ''Apply'' button');
Apply(DemoFig);
return;


%%%
%%%  Sub-Function - Apply
%%%

function Apply(DemoFig)

if nargin<1
   DemoFig = gcbf;
end

handles = get(DemoFig,'UserData');

hSrcImage=handles.SrcImage;
hDstImage=handles.DstImage;

set(DemoFig,'Pointer','watch');
setstatus(DemoFig, 'Calculating flow...'); drawnow;

srcImage = get(hSrcImage, 'CData');
dstImage = get(hDstImage, 'CData');

featuresA = get(hSrcImage, 'UserData');

winSize = [10, 10];
level = 2;
criteria = [20, 0.03];

[featuresB, error] = cvCalcOpticalFlowPyrLK(srcImage, dstImage, ...
    [featuresA(:,2)-1, featuresA(:,1)-1], [featuresA(:,2)-1, featuresA(:,1)-1], ...
    winSize, level, criteria);
featuresB = [featuresB(:,2), featuresB(:,1)]+1;

set(hDstImage, 'UserData', featuresB);
FeaturesUpdate(DemoFig);

setstatus(DemoFig, 'Done');
set(DemoFig,'Pointer','arrow'); drawnow
return


%%%
%%%  Sub-function - ControlsUpdate
%%%

function ControlsUpdate(DemoFig)

if nargin<1
   DemoFig = gcbf;
end;

handles = get(DemoFig,'UserData');

hNumEdit = handles.NumEdit;

% num value
oldv = get(hNumEdit, 'UserData');
newv = str2num(get(hNumEdit, 'String'));
if isempty(newv) | newv(1) < 1 | newv(1) > 100
    newv = oldv;
end
set(hNumEdit, 'String', num2str(newv(1)));
set(hNumEdit, 'UserData', newv(1));

setstatus(DemoFig, 'Press ''Generate'' button');
return;

%%%
%%%  Sub-function - FeaturesUpdate
%%%

function FeaturesUpdate(DemoFig)
if nargin<1
   DemoFig = gcbf;
end;

pointSize = 10; % size of point cross
width     = 2;  % width of cross lines

handles = get(DemoFig,'UserData');

hSrcAx     = handles.SrcAx;
hDstAx     = handles.DstAx;

hSrcImage = handles.SrcImage;
hDstImage = handles.DstImage;

hFeaturesA = get(hSrcAx, 'UserData');
hFeaturesB = get(hDstAx, 'UserData');

featuresA = get(hSrcImage, 'UserData');
featuresB = get(hDstImage, 'UserData');

delete(hFeaturesA(:));
delete(hFeaturesB(:));
hFeaturesA = [];
hFeaturesB = [];
% draw featuresA
for fnum = 1:size(featuresA,1)
    hFeaturesA(2*fnum - 1) = line('Parent', hSrcAx, ...
        'XData', [featuresA(fnum, 1)-pointSize featuresA(fnum, 1)+pointSize], ...
        'YData', [featuresA(fnum, 2) featuresA(fnum, 2)], ...
        'Color', 'blue', 'LineWidth', width);
    hFeaturesA(2*fnum) = line('Parent', hSrcAx, ...
        'XData', [featuresA(fnum, 1) featuresA(fnum, 1)], ...
        'YData', [featuresA(fnum, 2)-pointSize featuresA(fnum, 2)+pointSize], ...
        'Color', 'blue', 'LineWidth', width);
end
% draw featuresB
% If flow was not found, when red cross with featureA coordinates is drawn
for fnum = 1:size(featuresB,1)
    if isnan(featuresB(1)) == 1
        hFeaturesB(2*fnum - 1) = line('Parent', hDstAx, ...
            'XData', [featuresA(fnum, 1)-pointSize featuresA(fnum, 1)+pointSize], ...
            'YData', [featuresA(fnum, 2) featuresA(fnum, 2)], ...
            'Color', 'red', 'LineWidth', width);
        hFeaturesB(2*fnum) = line('Parent', hDstAx, ...
            'XData', [featuresA(fnum, 1) featuresA(fnum, 1)], ...
            'YData', [featuresA(fnum, 2)-pointSize featuresA(fnum, 2)+pointSize], ...
            'Color', 'red', 'LineWidth', width);
    else
        hFeaturesB(2*fnum - 1) = line('Parent', hDstAx, ...
            'XData', [featuresB(fnum, 1)-pointSize featuresB(fnum, 1)+pointSize], ...
            'YData', [featuresB(fnum, 2) featuresB(fnum, 2)], ...
            'Color', 'blue', 'LineWidth', width);
        hFeaturesB(2*fnum) = line('Parent', hDstAx, ...
            'XData', [featuresB(fnum, 1) featuresB(fnum, 1)], ...
            'YData', [featuresB(fnum, 2)-pointSize featuresB(fnum, 2)+pointSize], ...
            'Color', 'blue', 'LineWidth', width);
    end
end

set(hSrcAx, 'UserData', hFeaturesA);
set(hDstAx, 'UserData', hFeaturesB);
return;

%%%
%%%  Sub-function - GetFeatures
%%%

function GetFeatures(DemoFig)
if nargin<1
   DemoFig = gcbf;
end;

handles = get(DemoFig,'UserData');

hSrcAx     = handles.SrcAx;

hSrcImage = handles.SrcImage;
hDstImage = handles.DstImage;

srcImage = get(hSrcImage, 'CData');

featuresA = get(hSrcImage, 'UserData');
featuresB = get(hDstImage, 'UserData');

set(hSrcImage, 'UserData', []);
set(hDstImage, 'UserData', []);
FeaturesUpdate(DemoFig);

[x, y] = getpts(hSrcAx);
imgSize = [size(srcImage,2), size(srcImage,1)];
points = [x, y];
points(points(:,1)<1 | points(:,1) > imgSize(1) | ...
    points(:,2)<1 | points(:,2) > imgSize(2) ,:) = [];
if ~isempty(points)
    featuresA = points;
    featuresB = [];
    setstatus(DemoFig, 'Press ''Apply'' button');
end
set(hSrcImage, 'UserData', featuresA);
set(hDstImage, 'UserData', featuresB);
FeaturesUpdate(DemoFig);
return;

%%%
%%%  Sub-function - GoodFeatures
%%%

function GoodFeatures(DemoFig)
if nargin<1
   DemoFig = gcbf;
end;

handles = get(DemoFig,'UserData');

hSrcAx    = handles.SrcAx;
hNumEdit  = handles.NumEdit;
hSrcImage = handles.SrcImage;
hDstImage = handles.DstImage;

srcImage = get(hSrcImage, 'CData');

featuresA = get(hSrcImage, 'UserData');
featuresB = get(hDstImage, 'UserData');

set(hSrcImage, 'UserData', []);
set(hDstImage, 'UserData', []);
FeaturesUpdate(DemoFig);

numFeatures = get(hNumEdit, 'UserData');
qualityLevel = 0.1;
minDistance  = size(srcImage, 1) / 5;
points = cvGoodFeaturesToTrack(srcImage, numFeatures, ...
    qualityLevel, minDistance);
points = [points(:, 2), points(:, 1)] + 1;
if ~isempty(points)
    featuresA = points;
    featuresB = [];
    setstatus(DemoFig, 'Press ''Apply'' button');
else
    setstatus(DemoFig, 'The features were not found');
end
set(hSrcImage, 'UserData', featuresA);
set(hDstImage, 'UserData', featuresB);
FeaturesUpdate(DemoFig);
return;