function varargout = cvpyrdown(varargin)
%CVPYRDOWN         Downscale the image.
%   IMAGE dst = cvpyrdown(IMAGE src);
%
if nargin ~= 1
    error 'Invalid number of parameters';
    return;
end

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'PyrDown', varargin{:});
else
    feval('cvwrap', 'PyrDown', varargin{:});
end
return;
