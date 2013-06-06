function yp = yprime(t,y)
%YPRIME  Define differential equations for restricted three-body problem.
%   YP = YPRIME(T,Y) defines a system of ordinary differential
%   equations representing the motion of a body of small mass
%   in orbit about the earth and moon. This is a simple example
%   of the "restricted three-body problem," which models the
%   motion of a body of small mass in the vicinity of two other
%   massive bodies.
%
%   The coordinate system moves with the earth-moon system.
%   The 1-axis goes through the centers of the earth and the moon.
%   The 2-axis is perpendicular, in the plane of motion of the third body.
%   The origin is at the center of gravity of the two heavy bodies.
%   Let mu = the ratio of the mass of the moon to the mass of the earth.
%   The earth is located at (-mu,0) and the moon at (1-mu,0).
%
%   T represents time. It is ignored in YPRIME because the differential
%   equations are not functions of time.
%
%   Y is a column or row vector with 4 elements. 
%   Y(1) and Y(3) = coordinates of the third body.
%   Y(2) and Y(4) = velocity of the third body.
%
%   The output YP is a column vector with 4 elements representing
%   derivatives of y with respect to t given the input Y.
%
%   YPRIME is suitable as input to one of the ODE solvers, such as ODE23.
%   For example:
%
%   [t,y]=ode23(@yprime,[0 1],[0 1 2 3])

% Copyright 1984-2006 The MathWorks, Inc.
% All Rights Reserved.

mu = 1/82.45;
mus = 1-mu;
r1 = norm([y(1)+mu, y(3)]);   % Distance to the earth
r2 = norm([y(1)-mus, y(3)]);  % Distance to the moon
yp(1) = y(2);
yp(2) = 2*y(4) + y(1) - mus*(y(1)+mu)/r1^3 - mu*(y(1)-mus)/r2^3;
yp(3) = y(4);
yp(4) = -2*y(2) + y(3) - mus*y(3)/r1^3 - mu*y(3)/r2^3;
% yp = yp';
