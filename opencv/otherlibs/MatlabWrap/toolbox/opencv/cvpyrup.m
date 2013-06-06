function varargout = cvpyrup(varargin)
%CVPYRUP         Upscale the image.
%   IMAGE dst = cvpyrup(IMAGE src);
%
if nargin ~= 1
    error 'Invalid number of parameters';
    return;
end

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'PyrUp', varargin{1}, 7);
else
    feval('cvwrap', 'PyrUp', varargin{1}, 7);
end
return;
