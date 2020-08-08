%%
function likehood=PF_MeasurementFcn(particles,measurement)

yHat=particles(1,:);
e=bsxfun(@minus,yHat,measurement(:)');
numberOfMeasurements=1;

mu=0;
Sigma=eye(numberOfMeasurements);
measurementErrorProd=dot((e-mu),Sigma\(e-mu),1);
c=1/sqrt((2*pi)^numberOfMeasurements*det(Sigma));
likehood=c*exp(-0.5*measurementErrorProd);

end