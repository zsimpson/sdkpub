function varargout = cvdilate(varargin)
%CVDILATE        Dilate image.
%   IMAGE dst = cvdilate(IMAGE src, [elem_cols elem_rows elem_anchor_x elem_anchor_y], elem_type, iterations );
%   elem_type:
%     0 - rectangle
%     1 - cross
%     2 - ellipse
%
if nargin ~= 4
    error 'Invalid number of parameters';
    return;
end

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'Dilate', varargin{:});
else
    feval('cvwrap', 'Dilate', varargin{:});
end
return;
