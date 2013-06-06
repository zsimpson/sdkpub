function tbxStruct=demos
%DEMOS Demo list for the OpenCV toolbox.

if nargout==0, demo toolbox; return; end

tbxStruct.Name='OpenCV';
tbxStruct.Type='toolbox';

tbxStruct.Help= {
    'OpenCV is the powerfull'
    'computer vision library'
    ' '
     };

tbxStruct.DemoList={
    'Contour Demo', 'contdemo',
    'Flood Fill Demo', 'filldemo'
    'Optical Flow Demo', 'flowdemo'
};
