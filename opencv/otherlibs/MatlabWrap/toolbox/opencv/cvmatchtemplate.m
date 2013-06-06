function varargout = cvmatchtemplate(varargin)
%CVMATCHTEMPLATE      Match template against every location within the image.
%   IMAGE dst = cvmatchtemplate(IMAGE src, IMAGE template, method );
%   method:
%     0 - squared difference
%     1 - normalized squared difference
%     2 - cross correlation
%     3 - normalized cross correlation
%     4 - correlation coefficient
%     5 - normalized correlation coefficient
%
if nargin ~= 3
    error 'Invalid number of parameters';
    return;
end

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'MatchTemplate', varargin{:});
else
    feval('cvwrap', 'MatchTemplate', varargin{:});
end
return;
