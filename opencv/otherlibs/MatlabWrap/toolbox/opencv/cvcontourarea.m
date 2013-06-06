function varargout = cvcontourarea(varargin)
%CVCONTOURAREA       Calculate contour area.
%   area = cvContourArea(contour);
%   contour - m by 2 matrix of contour's points
%
%   area = cvContourArea(contour, slice);
%   contour - m by 2 matrix of contour's points
%   slice   - [startIdx endIdx]

if nargin < 1 | nargin > 2
    error 'Invalid number of parameters';
    return;
end

contSize = size(varargin{1});
if ~isnumeric(varargin{1}) | ndims(varargin{1}) ~= 2 | ...
    contSize(1) < 1 | contSize(2) ~= 2
    error 'Invalid parameter ''contour''';
    return;
end;

if nargin > 1
    sliceSize = size(varargin{2});
	if ~isnumeric(varargin{2}) | ndims(varargin{2}) ~= 2 | ...
        sliceSize(1) ~= 1 | sliceSize(2) ~= 2
        error 'Invalid parameter ''slice''';
        return;
	end;    
else
    % default: whole contour
    varargin{2} = [1 contSize(1)+1];
end;

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'ContourArea', varargin{:});
else
    feval('cvwrap', 'ContourArea', varargin{:});
end
return;