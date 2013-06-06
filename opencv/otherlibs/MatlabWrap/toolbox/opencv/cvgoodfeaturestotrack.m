function varargout = cvgoodfeaturestotrack(varargin)
%CVGOODFEATURESTOTRACK Find strong corners on the image.
%   corners = cvGoodFeaturesToTrack(IMAGE image, corner_count,
%     quality_level, min_distance);
%   corners = cvGoodFeaturesToTrack(IMAGE image, corner_count,
%     quality_level, min_distance, IMAGE mask);
%
%   image         - input image
%   corner_count  - number of output corners
%   quality_level - only those corners are selected, which minimal eigen value is
%                   non-less than maximum of minimal eigen values on the image,
%                   multiplied by quality_level. For example, quality_level = 0.1
%                   means that selected corners must be at least 1/10 as good as
%                   the best corner.
%   min_distance  - The selected corners(after thresholding using quality_level)
%                   are rerified such that pair-wise distance between them is
%                   non-less than min_distance
%   mask          - mask image
%
%   corners       - output corners
%   All points coordinates have 0-based [y x] format

if nargin < 4 | nargin > 5
    error 'Invalid number of parameters';
    return;
end

if nargin < 5
    varargin{5} = [];
end;

out = nargout;
if out < 1
    out = 1;
end

if out > 1
    error 'Too many output parameters'
    return;
end;

[varargout{1:1}] = feval('cvwrap', 'GoodFeaturesToTrack', varargin{:});

return;