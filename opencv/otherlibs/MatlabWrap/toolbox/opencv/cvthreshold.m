function varargout = cvthreshold(varargin)
%CVTHRESHOLD         Threshold image.
%   IMAGE dst = cvThreshold(IMAGE src, DOUBLE thresh,
%     DOUBLE maxVal, type);
%   type:
%     'binary'      - val = (val>thresh? MAX:0)
%     'binary_inv'  - val = (val>thresh? 0:MAX)
%     'trunc'       - val = (val>thresh? thresh:val)
%     'tozero'      - val = (val>thresh? val:0)
%     'tozero_inv'  - val = (val>thresh? 0:val)

if nargin ~= 4
    error 'Invalid number of parameters';
    return;
end
if ~ischar(varargin{4})
    error 'Invalid parameter ''type''';
    return;
end;

type_t = {'binary', 'binary_inv', 'trunc', 'tozero', 'tozero_inv'};
type_i = [0, 1, 2, 3, 4];
idx = strmatch(varargin{4}, type_t, 'exact');
if isempty(idx)
    error 'Invalid parameter ''type''';
    return;
end
varargin{4} = type_i(idx(1));

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'Threshold', varargin{:});
else
    feval('cvwrap', 'Threshold', varargin{:});
end
return;