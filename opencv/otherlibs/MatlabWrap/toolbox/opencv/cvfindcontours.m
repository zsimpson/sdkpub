function varargout = cvfindcontours(varargin)
%CVFINDCONTOURS      Find contours on binary image.
%   SEQARRAY dst = cvFindContours(IMAGE src, mode, method);
%   mode:
%     'external'
%    {'list'}
%     'ccomp'
%     'tree'
%   method:
%     'none'
%    {'simple'}
%     'tc89_l1'
%     'tc89_kcos'

if nargin < 1 | nargin > 3
    error 'Invalid number of parameters';
    return;
end

if nargin > 1 
    if ~ischar(varargin{2})
        error 'Invalid parameter ''mode''';
        return;
    end;
	mode_t = {'external', 'list', 'ccomp', 'tree'};
	mode_i = [0, 1, 2, 3];
    idx = strmatch(varargin{2}, mode_t, 'exact');
    if isempty(idx)
        error 'Invalid parameter ''mode''';
        return;
	end
    varargin{2} = mode_i(idx(1));
else
    % default
    varargin{2} = 1;
end % mode

if nargin > 2 
    if ~ischar(varargin{3})
        error 'Invalid parameter ''method''';
        return;
    end;
	method_t = {'none', 'simple', 'tc89_l1', 'tc89_kcos'};
	method_i = [1, 2, 3, 4];
    idx = strmatch(varargin{3}, method_t, 'exact');
    if isempty(idx)
        error 'Invalid parameter ''method''';
        return;
	end
    varargin{3} = method_i(idx(1));
else
    % default
    varargin{3} = 2;
end % method

if nargout > 0
    [varargout{1:nargout}] = feval('cvwrap', 'FindContours', varargin{:});
else
    feval('cvwrap', 'FindContours', varargin{:});
end
return;