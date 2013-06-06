function varargout = cvapproxpoly(varargin)
%CVAPPROXPOLY        Approximate poligonal curve.
%   SEQARRAY dst = cvApproxPoly(SEQARRAY contours, first, method,
%     parameter, recursive);
%   contours      - struct array of contours
%   first         - number in struct array 'contours' of start contour
%   method:
%     'dp'        - Douglas-Peucker method
%   parameter     - desired accuracy
%   recursive     - {0} | 1

if nargin < 4 | nargin > 5
    error 'Invalid number of parameters';
    return;
end

if ~ischar(varargin{3})
    error 'Invalid parameter ''method''';
    return;
end;
method_t = {'dp'};
method_i = [0];
idx = strmatch(varargin{3}, method_t, 'exact');
if isempty(idx)
    error 'Invalid parameter ''method''';
    return;
end
varargin{3} = method_i(idx(1));

if nargin < 5 
    % default
    varargin{5} = 0;
end % recursive

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'ApproxPoly', varargin{:});
else
    feval('cvwrap', 'ApproxPoly', varargin{:});
end
return;