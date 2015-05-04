function profile = GenerateIndividualProfileTestCase%(directoryName)
directoryName = 'GeneratedProfileV0.3';

fidLog = fopen(strcat('/',directoryName,'/','log.txt'));

temp = fgetl(fidLog);
temp = fgetl(fidLog); % disregard first two lines

% version number
line = fgetl(fidLog);
tabLocation = strfind(line,sprintf('\t'));
profile.version = str2double(line(tabLocation(1):end));

temp = fgetl(fidLog);

% lat
line = fgetl(fidLog);
tabLocation = strfind(line,sprintf('\t'));
profile.lat = str2double(line(tabLocation(1):end));

% lon
line = fgetl(fidLog);
tabLocation = strfind(line,sprintf('\t'));
profile.lon = str2double(line(tabLocation(1):end));

% depth limits
line = fgetl(fidLog);
tabLocation = strfind(line,sprintf('\t'));
profile.zmin = -str2double(line(tabLocation(1):end));
line = fgetl(fidLog);
tabLocation = strfind(line,sprintf('\t'));
profile.zmax = -str2double(line(tabLocation(1):end));
line = fgetl(fidLog);
tabLocation = strfind(line,sprintf('\t'));
profile.res = str2double(line(tabLocation(1):end));

fclose(fidLog);

% open surface depths file
fidSurfDep = fopen(strcat('/',directoryName,'/','SurfacesAtIndividualLocation.txt'));

temp = fgetl(fidSurfDep);

count = 1;
while ~feof(fidSurfDep)
    line = fgetl(fidLog);
    tabLocation = strfind(line,sprintf('\t'));
    profile.surfName{count} = line(1:tabLocation(1)-2)
    profile.surfDep(count) = str2double(line(tabLocation(1):end))
    count = count + 1
    
end
fclose(fidSurfDep);



% open primary data file
fidProfile = fopen(strcat('/',directoryName,'/','ProfileAtIndividualLocation.txt'));

temp = fgetl(fidProfile);
temp = fgetl(fidProfile); % discard first two lines
count = 1;
while ~feof(fidProfile)
    line = fgetl(fidProfile);
    tabLocations = strfind(line,sprintf('\t'));
    
    profile.dep(count) = str2double(line(1:tabLocations(1)));
    profile.vp(count) = str2double(line(tabLocations(1):tabLocations(2)));
    profile.vs(count) = str2double(line(tabLocations(2):tabLocations(3)));
    profile.rho(count) = str2double(line(tabLocations(3):end));
    count = count + 1;
end

fclose(fidProfile);





end