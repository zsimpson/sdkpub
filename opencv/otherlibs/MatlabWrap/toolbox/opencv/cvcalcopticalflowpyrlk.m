function varargout = cvcalcopticalflowpyrlk(varargin)
%CVCALCOPTICALFLOWPYRLK Calculate optical flow between two images for certain set of points.
%   [featuresB, error] = cvCalcOpticalFlowPyrLK(IMAGE imgA, IMAGE imgB,
%     featuresA, guessFeaturesB,
%     winSize, level, [maxIter epsilon]);
%
%   imgA              - first frame
%   imgB              - second frame
%   featuresA         - [n][2] array of feature points on the first frame
%   guessFeaturesB    - [n][2] initial guessess about newfeatures' locations.
%     May be empty.
%   winSize           - [height width] size of search window
%   level             - maximal pyramid level number
%   [maxIter epsilon] - specify when to stop search process.
%     One of them may be 0.
%
%   featuresB         - calculated feature points positions.
%     Coordinates of points for which flow was not found are [NaN NaN]
%   error             - array of differences between
%     patches around the original and moved points
%   All points coordinates have 0-based [y x] format

if nargin ~= 7
    error 'Invalid number of parameters';
    return;
end

out = nargout;
if out < 1
    out = 1;
end

if out > 2
    error 'Too many output parameters'
    return;
end;
for idx = out+1:2
    varargout{idx} = [];
end

[varargout{1:2}] = feval('cvwrap', 'CalcOpticalFlowPyrLK', varargin{:});

return;