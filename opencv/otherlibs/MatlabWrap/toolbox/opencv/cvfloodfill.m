function varargout = cvfloodfill(varargin)
%CVFLOODFILL         Fill connected domain.
%   [dst area value rect] = cvFloodFill(src, seedPoint, newVal,
%     loDiff, upDiff, connectivity);
%   src          - input image
%   seedPoint    - [y x]
%   newVal
%   loDiff
%   upDiff
%   connectivity - default 4
%
%   dst   - destination image
%   area  - area of the segmented component
%   value - gray scale value of the segmented component
%   rect  - ROI of the segmented component


if nargin < 5 | nargin > 6
    error 'Invalid number of parameters';
    return;
end

if nargin > 5
    if varargin{6} ~= 4 & varargin{6} ~= 8
        error 'Invalid 'connectivity' parameter';
        return;
    end
else
    % default value
    varargin{6} = 4;
end

out = nargout;
if out < 1
    out = 1;
end

if out > 4
    error 'Too many output parameters'
    return;
end;
for idx = out+1:4
    varargout{idx} = [];
end

if out > 0
    [varargout{1:4}] = feval('cvwrap', 'FloodFill', varargin{:});
else
    feval('cvwrap', 'FloodFill', varargin{:});
end
return;