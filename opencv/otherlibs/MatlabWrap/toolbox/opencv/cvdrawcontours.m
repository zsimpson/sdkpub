function varargout = cvdrawcontours(varargin)
%CVDRAWCONTOURS      Draw contours.
%   IMAGE dst = cvDrawContours(IMAGE src, SEQARRAY contours, first,
%     externalColor, holeColor, maxLevel, thickness, connectivity );
%   src           - source image
%   contours      - struct array of contours
%   first         - number in struct array 'contours' of start contour
%   externalColor -
%   holeColor     -
%   maxLevel      - 
%   thickness     - default 1. For filling contours use -1
%   connectivity  - default 8
%
%   dst           - destination image

if nargin < 6 | nargin > 8
    error 'Invalid number of parameters';
    return;
end

if nargin > 6
    if varargin{7} < 0 & varargin{7} ~= -1
        error 'Invalid 'thickness' parameter';
        return;
    end
else
    % default value
    varargin{7} = 1;
end

if nargin > 7
    if varargin{8} ~= 4 & varargin{8} ~= 8
        error 'Invalid 'connectivity' parameter';
        return;
    end
else
    % default value
    varargin{8} = 8;
end

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'DrawContours', varargin{:});
else
    feval('cvwrap', 'DrawContours', varargin{:});
end
return;