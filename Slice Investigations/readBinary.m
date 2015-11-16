function readBinary
clc
fileName = 'rho3dfile.d';
fileNameSwap = 'rho3dfileSwap.d';

sizeA = [2 4];
fileID = fopen(fileName);
% fileIDSwap = fopen(fileNameSwap);


Raw = fread(fileID,sizeA,'single','l')
% Swapped = fread(fileIDSwap,sizeA,'single','l')


fclose(fileID);
% fclose(fileIDSwap);
end