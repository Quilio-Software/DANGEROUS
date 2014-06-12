CREATE TABLE SAFEEqualiserUserData (

ID int NOT NULL AUTO_INCREMENT,
Descriptors varchar(256),
usrIP varchar(256),
numInputs int, 
numOutputs int,
Param_Band1Gain double,
Param_Band1Frequency double,
Param_Band2Gain double,
Param_Band2Frequency double,
Param_Band2QFactor double,
Param_Band3Gain double,
Param_Band3Frequency double,
Param_Band3QFactor double,
Param_Band4Gain double, 
Param_Band4Frequency double,
Param_Band4QFactor double,                    
Param_Band5Gain double,
Param_Band5Frequency double,
Metadata_Genre varchar(256),
Metadata_Instrument varchar(256),
Metadata_Location varchar(256),
Metadata_Experience varchar(256),
Metadata_Age varchar(256),
Metadata_Language varchar(256),
FeatureChecksum char(32),
PRIMARY KEY (ID)
);

CREATE TABLE SAFEEqualiserAudioFeatureData (

ID int,
ChannelNumber int,
FrameNumber int,
SignalState varchar(256),
DataMean double,
Variance double,
Standard_Deviation double,
RMS_Amplitude double,
Zero_Crossing_Rate double,
Spectral_Centroid double,
Spectral_Variance double,
Spectral_Standard_Deviation double,
Spectral_Skewness double,
Spectral_Kurtosis double,
Irregularity_J double,
Irregularity_K double,
Fundamental double,
Smoothness double,
Spectral_Roll_Off double,
Spectral_Flatness double,
Tonality double,
Spectral_Crest double,
Spectral_Slope double,
Peak_Spectral_Centroid double,
Peak_Spectral_Variance double,
Peak_Spectral_Standard_Deviation double,
Peak_Spectral_Skewness double,
Peak_Spectral_Kurtosis double,
Peak_Irregularity_J double,
Peak_Irregularity_K double,
Peak_Tristimulus_1 double,
Peak_Tristimulus_2 double,
Peak_Tristimulus_3 double,
Inharmonicity double,
Harmonic_Spectral_Centroid double,
Harmonic_Spectral_Variance double,
Harmonic_Spectral_Standard_Deviation double,
Harmonic_Spectral_Skewness double,
Harmonic_Spectral_Kurtosis double,
Harmonic_Irregularity_J double,
Harmonic_Irregularity_K double,
Harmonic_Tristimulus_1 double,
Harmonic_Tristimulus_2 double,
Harmonic_Tristimulus_3 double,
Noisiness double,
Parity_Ratio double,
Bark_Coefficient_0 double,
Bark_Coefficient_1 double,
Bark_Coefficient_2 double,
Bark_Coefficient_3 double,
Bark_Coefficient_4 double,
Bark_Coefficient_5 double,
Bark_Coefficient_6 double,
Bark_Coefficient_7 double,
Bark_Coefficient_8 double,
Bark_Coefficient_9 double,
Bark_Coefficient_10 double,
Bark_Coefficient_11 double,
Bark_Coefficient_12 double,
Bark_Coefficient_13 double,
Bark_Coefficient_14 double,
Bark_Coefficient_15 double,
Bark_Coefficient_16 double,
Bark_Coefficient_17 double,
Bark_Coefficient_18 double,
Bark_Coefficient_19 double,
Bark_Coefficient_20 double,
Bark_Coefficient_21 double,
Bark_Coefficient_22 double,
Bark_Coefficient_23 double,
Bark_Coefficient_24 double,
MFCC_0 double,
MFCC_1 double,
MFCC_2 double,
MFCC_3 double,
MFCC_4 double,
MFCC_5 double,
MFCC_6 double,
MFCC_7 double,
MFCC_8 double,
MFCC_9 double,
MFCC_10 double,
MFCC_11 double,
MFCC_12 double,
FOREIGN KEY (ID) REFERENCES SAFEEqualiserUserData (ID),
PRIMARY KEY (ID, ChannelNumber, FrameNumber, SignalState)
);

