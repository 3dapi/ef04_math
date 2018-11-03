
#include <Windows.h>

#include <stdio.h>
#include <math.h>


#define DGX_PI			3.1415926535897932384626433832795
#define ONE_RADtoDEG	57.295779513082321
#define ONE_DEGtoRAD	0.0174532925199433
#define DEG90toRAD		1.5707963267948966
#define DGXToRadian(d)	(float)((d) * DGX_PI / 180.0)
#define DGXToDegree(r)	(float)((r) * 180.0  / DGX_PI)
#define RADtoDEG(v)		(float)( (v)*ONE_RADtoDEG)
#define DEGtoRAD(v)		(float)( (v)*ONE_DEGtoRAD)


static	unsigned int g_cos[364] = {
0X3f800000, 0X3f7ff605, 0X3f7fd814, 0X3f7fa62f, 0X3f7f605c, 0X3f7f069e, 
0X3f7e98fd, 0X3f7e1781, 0X3f7d8235, 0X3f7cd925, 0X3f7c1c5c, 0X3f7b4beb, 
0X3f7a67e2, 0X3f797051, 0X3f78654d, 0X3f7746ea, 0X3f76153f, 0X3f74d063, 
0X3f737871, 0X3f720d81, 0X3f708fb2, 0X3f6eff20, 0X3f6d5bec, 0X3f6ba635, 
0X3f69de1d, 0X3f6803ca, 0X3f66175e, 0X3f641901, 0X3f6208da, 0X3f5fe714, 
0X3f5db3d7, 0X3f5b6f51, 0X3f5919ae, 0X3f56b31d, 0X3f543bce, 0X3f51b3f3, 
0X3f4f1bbd, 0X3f4c7360, 0X3f49bb13, 0X3f46f30a, 0X3f441b7d, 0X3f4134a6, 
0X3f3e3ebd, 0X3f3b39ff, 0X3f3826a7, 0X3f3504f3, 0X3f31d522, 0X3f2e9772, 
0X3f2b4c25, 0X3f27f37c, 0X3f248dbb, 0X3f211b24, 0X3f1d9bfe, 0X3f1a108d, 
0X3f167918, 0X3f12d5e8, 0X3f0f2744, 0X3f0b6d77, 0X3f07a8ca, 0X3f03d989, 
0X3f000000, 0X3ef838f7, 0X3ef05e94, 0X3ee87171, 0X3ee0722f, 0X3ed8616c, 
0X3ed03fc9, 0X3ec80de9, 0X3ebfcc6f, 0X3eb77c01, 0X3eaf1d44, 0X3ea6b0df, 
0X3e9e377a, 0X3e95b1be, 0X3e8d2057, 0X3e8483ee, 0X3e77ba60, 0X3e665992, 
0X3e54e6cd, 0X3e43636f, 0X3e31d0d4, 0X3e20305b, 0X3e0e8365, 0X3df996a2, 
0X3dd61305, 0X3db27eb6, 0X3d8edc7b, 0X3d565e3a, 0X3d0ef2c6, 0X3c8ef859, 
0X00000000, 0Xbc8ef859, 0Xbd0ef2c6, 0Xbd565e3a, 0Xbd8edc7b, 0Xbdb27eb6, 
0Xbdd61305, 0Xbdf996a2, 0Xbe0e8365, 0Xbe20305b, 0Xbe31d0d4, 0Xbe43636f, 
0Xbe54e6cd, 0Xbe665992, 0Xbe77ba60, 0Xbe8483ee, 0Xbe8d2057, 0Xbe95b1be, 
0Xbe9e377a, 0Xbea6b0df, 0Xbeaf1d44, 0Xbeb77c01, 0Xbebfcc6f, 0Xbec80de9, 
0Xbed03fc9, 0Xbed8616c, 0Xbee0722f, 0Xbee87171, 0Xbef05e94, 0Xbef838f7, 
0Xbf000000, 0Xbf03d989, 0Xbf07a8ca, 0Xbf0b6d77, 0Xbf0f2744, 0Xbf12d5e8, 
0Xbf167918, 0Xbf1a108d, 0Xbf1d9bfe, 0Xbf211b24, 0Xbf248dbb, 0Xbf27f37c, 
0Xbf2b4c25, 0Xbf2e9772, 0Xbf31d522, 0Xbf3504f3, 0Xbf3826a7, 0Xbf3b39ff, 
0Xbf3e3ebd, 0Xbf4134a6, 0Xbf441b7d, 0Xbf46f30a, 0Xbf49bb13, 0Xbf4c7360, 
0Xbf4f1bbd, 0Xbf51b3f3, 0Xbf543bce, 0Xbf56b31d, 0Xbf5919ae, 0Xbf5b6f51, 
0Xbf5db3d7, 0Xbf5fe714, 0Xbf6208da, 0Xbf641901, 0Xbf66175e, 0Xbf6803ca, 
0Xbf69de1d, 0Xbf6ba635, 0Xbf6d5bec, 0Xbf6eff20, 0Xbf708fb2, 0Xbf720d81, 
0Xbf737871, 0Xbf74d063, 0Xbf76153f, 0Xbf7746ea, 0Xbf78654d, 0Xbf797051, 
0Xbf7a67e2, 0Xbf7b4beb, 0Xbf7c1c5c, 0Xbf7cd925, 0Xbf7d8235, 0Xbf7e1781, 
0Xbf7e98fd, 0Xbf7f069e, 0Xbf7f605c, 0Xbf7fa62f, 0Xbf7fd814, 0Xbf7ff605, 
0Xbf800000, 0Xbf7ff605, 0Xbf7fd814, 0Xbf7fa62f, 0Xbf7f605c, 0Xbf7f069e, 
0Xbf7e98fd, 0Xbf7e1781, 0Xbf7d8235, 0Xbf7cd925, 0Xbf7c1c5c, 0Xbf7b4beb, 
0Xbf7a67e2, 0Xbf797051, 0Xbf78654d, 0Xbf7746ea, 0Xbf76153f, 0Xbf74d063, 
0Xbf737871, 0Xbf720d81, 0Xbf708fb2, 0Xbf6eff20, 0Xbf6d5bec, 0Xbf6ba635, 
0Xbf69de1d, 0Xbf6803ca, 0Xbf66175e, 0Xbf641901, 0Xbf6208da, 0Xbf5fe714, 
0Xbf5db3d7, 0Xbf5b6f51, 0Xbf5919ae, 0Xbf56b31d, 0Xbf543bce, 0Xbf51b3f3, 
0Xbf4f1bbd, 0Xbf4c7360, 0Xbf49bb13, 0Xbf46f30a, 0Xbf441b7d, 0Xbf4134a6, 
0Xbf3e3ebd, 0Xbf3b39ff, 0Xbf3826a7, 0Xbf3504f3, 0Xbf31d522, 0Xbf2e9772, 
0Xbf2b4c25, 0Xbf27f37c, 0Xbf248dbb, 0Xbf211b24, 0Xbf1d9bfe, 0Xbf1a108d, 
0Xbf167918, 0Xbf12d5e8, 0Xbf0f2744, 0Xbf0b6d77, 0Xbf07a8ca, 0Xbf03d989, 
0Xbf000000, 0Xbef838f7, 0Xbef05e94, 0Xbee87171, 0Xbee0722f, 0Xbed8616c, 
0Xbed03fc9, 0Xbec80de9, 0Xbebfcc6f, 0Xbeb77c01, 0Xbeaf1d44, 0Xbea6b0df, 
0Xbe9e377a, 0Xbe95b1be, 0Xbe8d2057, 0Xbe8483ee, 0Xbe77ba60, 0Xbe665992, 
0Xbe54e6cd, 0Xbe43636f, 0Xbe31d0d4, 0Xbe20305b, 0Xbe0e8365, 0Xbdf996a2, 
0Xbdd61305, 0Xbdb27eb6, 0Xbd8edc7b, 0Xbd565e3a, 0Xbd0ef2c6, 0Xbc8ef859, 
0X00000000, 0X3c8ef859, 0X3d0ef2c6, 0X3d565e3a, 0X3d8edc7b, 0X3db27eb6, 
0X3dd61305, 0X3df996a2, 0X3e0e8365, 0X3e20305b, 0X3e31d0d4, 0X3e43636f, 
0X3e54e6cd, 0X3e665992, 0X3e77ba60, 0X3e8483ee, 0X3e8d2057, 0X3e95b1be, 
0X3e9e377a, 0X3ea6b0df, 0X3eaf1d44, 0X3eb77c01, 0X3ebfcc6f, 0X3ec80de9, 
0X3ed03fc9, 0X3ed8616c, 0X3ee0722f, 0X3ee87171, 0X3ef05e94, 0X3ef838f7, 
0X3f000000, 0X3f03d989, 0X3f07a8ca, 0X3f0b6d77, 0X3f0f2744, 0X3f12d5e8, 
0X3f167918, 0X3f1a108d, 0X3f1d9bfe, 0X3f211b24, 0X3f248dbb, 0X3f27f37c, 
0X3f2b4c25, 0X3f2e9772, 0X3f31d522, 0X3f3504f3, 0X3f3826a7, 0X3f3b39ff, 
0X3f3e3ebd, 0X3f4134a6, 0X3f441b7d, 0X3f46f30a, 0X3f49bb13, 0X3f4c7360, 
0X3f4f1bbd, 0X3f51b3f3, 0X3f543bce, 0X3f56b31d, 0X3f5919ae, 0X3f5b6f51, 
0X3f5db3d7, 0X3f5fe714, 0X3f6208da, 0X3f641901, 0X3f66175e, 0X3f6803ca, 
0X3f69de1d, 0X3f6ba635, 0X3f6d5bec, 0X3f6eff20, 0X3f708fb2, 0X3f720d81, 
0X3f737871, 0X3f74d063, 0X3f76153f, 0X3f7746ea, 0X3f78654d, 0X3f797051, 
0X3f7a67e2, 0X3f7b4beb, 0X3f7c1c5c, 0X3f7cd925, 0X3f7d8235, 0X3f7e1781, 
0X3f7e98fd, 0X3f7f069e, 0X3f7f605c, 0X3f7fa62f, 0X3f7fd814, 0X3f7ff605, 
0X3f800000, 
};

static	unsigned int g_sin[364] = {
0X00000000, 0X3c8ef859, 0X3d0ef2c6, 0X3d565e3a, 0X3d8edc7b, 0X3db27eb6, 
0X3dd61305, 0X3df996a2, 0X3e0e8365, 0X3e20305b, 0X3e31d0d4, 0X3e43636f, 
0X3e54e6cd, 0X3e665992, 0X3e77ba60, 0X3e8483ee, 0X3e8d2057, 0X3e95b1be, 
0X3e9e377a, 0X3ea6b0df, 0X3eaf1d44, 0X3eb77c01, 0X3ebfcc6f, 0X3ec80de9, 
0X3ed03fc9, 0X3ed8616c, 0X3ee0722f, 0X3ee87171, 0X3ef05e94, 0X3ef838f7, 
0X3f000000, 0X3f03d989, 0X3f07a8ca, 0X3f0b6d77, 0X3f0f2744, 0X3f12d5e8, 
0X3f167918, 0X3f1a108d, 0X3f1d9bfe, 0X3f211b24, 0X3f248dbb, 0X3f27f37c, 
0X3f2b4c25, 0X3f2e9772, 0X3f31d522, 0X3f3504f3, 0X3f3826a7, 0X3f3b39ff, 
0X3f3e3ebd, 0X3f4134a6, 0X3f441b7d, 0X3f46f30a, 0X3f49bb13, 0X3f4c7360, 
0X3f4f1bbd, 0X3f51b3f3, 0X3f543bce, 0X3f56b31d, 0X3f5919ae, 0X3f5b6f51, 
0X3f5db3d7, 0X3f5fe714, 0X3f6208da, 0X3f641901, 0X3f66175e, 0X3f6803ca, 
0X3f69de1d, 0X3f6ba635, 0X3f6d5bec, 0X3f6eff20, 0X3f708fb2, 0X3f720d81, 
0X3f737871, 0X3f74d063, 0X3f76153f, 0X3f7746ea, 0X3f78654d, 0X3f797051, 
0X3f7a67e2, 0X3f7b4beb, 0X3f7c1c5c, 0X3f7cd925, 0X3f7d8235, 0X3f7e1781, 
0X3f7e98fd, 0X3f7f069e, 0X3f7f605c, 0X3f7fa62f, 0X3f7fd814, 0X3f7ff605, 
0X3f800000, 0X3f7ff605, 0X3f7fd814, 0X3f7fa62f, 0X3f7f605c, 0X3f7f069e, 
0X3f7e98fd, 0X3f7e1781, 0X3f7d8235, 0X3f7cd925, 0X3f7c1c5c, 0X3f7b4beb, 
0X3f7a67e2, 0X3f797051, 0X3f78654d, 0X3f7746ea, 0X3f76153f, 0X3f74d063, 
0X3f737871, 0X3f720d81, 0X3f708fb2, 0X3f6eff20, 0X3f6d5bec, 0X3f6ba635, 
0X3f69de1d, 0X3f6803ca, 0X3f66175e, 0X3f641901, 0X3f6208da, 0X3f5fe714, 
0X3f5db3d7, 0X3f5b6f51, 0X3f5919ae, 0X3f56b31d, 0X3f543bce, 0X3f51b3f3, 
0X3f4f1bbd, 0X3f4c7360, 0X3f49bb13, 0X3f46f30a, 0X3f441b7d, 0X3f4134a6, 
0X3f3e3ebd, 0X3f3b39ff, 0X3f3826a7, 0X3f3504f3, 0X3f31d522, 0X3f2e9772, 
0X3f2b4c25, 0X3f27f37c, 0X3f248dbb, 0X3f211b24, 0X3f1d9bfe, 0X3f1a108d, 
0X3f167918, 0X3f12d5e8, 0X3f0f2744, 0X3f0b6d77, 0X3f07a8ca, 0X3f03d989, 
0X3f000000, 0X3ef838f7, 0X3ef05e94, 0X3ee87171, 0X3ee0722f, 0X3ed8616c, 
0X3ed03fc9, 0X3ec80de9, 0X3ebfcc6f, 0X3eb77c01, 0X3eaf1d44, 0X3ea6b0df, 
0X3e9e377a, 0X3e95b1be, 0X3e8d2057, 0X3e8483ee, 0X3e77ba60, 0X3e665992, 
0X3e54e6cd, 0X3e43636f, 0X3e31d0d4, 0X3e20305b, 0X3e0e8365, 0X3df996a2, 
0X3dd61305, 0X3db27eb6, 0X3d8edc7b, 0X3d565e3a, 0X3d0ef2c6, 0X3c8ef859, 
0X00000000, 0Xbc8ef859, 0Xbd0ef2c6, 0Xbd565e3a, 0Xbd8edc7b, 0Xbdb27eb6, 
0Xbdd61305, 0Xbdf996a2, 0Xbe0e8365, 0Xbe20305b, 0Xbe31d0d4, 0Xbe43636f, 
0Xbe54e6cd, 0Xbe665992, 0Xbe77ba60, 0Xbe8483ee, 0Xbe8d2057, 0Xbe95b1be, 
0Xbe9e377a, 0Xbea6b0df, 0Xbeaf1d44, 0Xbeb77c01, 0Xbebfcc6f, 0Xbec80de9, 
0Xbed03fc9, 0Xbed8616c, 0Xbee0722f, 0Xbee87171, 0Xbef05e94, 0Xbef838f7, 
0Xbf000000, 0Xbf03d989, 0Xbf07a8ca, 0Xbf0b6d77, 0Xbf0f2744, 0Xbf12d5e8, 
0Xbf167918, 0Xbf1a108d, 0Xbf1d9bfe, 0Xbf211b24, 0Xbf248dbb, 0Xbf27f37c, 
0Xbf2b4c25, 0Xbf2e9772, 0Xbf31d522, 0Xbf3504f3, 0Xbf3826a7, 0Xbf3b39ff, 
0Xbf3e3ebd, 0Xbf4134a6, 0Xbf441b7d, 0Xbf46f30a, 0Xbf49bb13, 0Xbf4c7360, 
0Xbf4f1bbd, 0Xbf51b3f3, 0Xbf543bce, 0Xbf56b31d, 0Xbf5919ae, 0Xbf5b6f51, 
0Xbf5db3d7, 0Xbf5fe714, 0Xbf6208da, 0Xbf641901, 0Xbf66175e, 0Xbf6803ca, 
0Xbf69de1d, 0Xbf6ba635, 0Xbf6d5bec, 0Xbf6eff20, 0Xbf708fb2, 0Xbf720d81, 
0Xbf737871, 0Xbf74d063, 0Xbf76153f, 0Xbf7746ea, 0Xbf78654d, 0Xbf797051, 
0Xbf7a67e2, 0Xbf7b4beb, 0Xbf7c1c5c, 0Xbf7cd925, 0Xbf7d8235, 0Xbf7e1781, 
0Xbf7e98fd, 0Xbf7f069e, 0Xbf7f605c, 0Xbf7fa62f, 0Xbf7fd814, 0Xbf7ff605, 
0Xbf800000, 0Xbf7ff605, 0Xbf7fd814, 0Xbf7fa62f, 0Xbf7f605c, 0Xbf7f069e, 
0Xbf7e98fd, 0Xbf7e1781, 0Xbf7d8235, 0Xbf7cd925, 0Xbf7c1c5c, 0Xbf7b4beb, 
0Xbf7a67e2, 0Xbf797051, 0Xbf78654d, 0Xbf7746ea, 0Xbf76153f, 0Xbf74d063, 
0Xbf737871, 0Xbf720d81, 0Xbf708fb2, 0Xbf6eff20, 0Xbf6d5bec, 0Xbf6ba635, 
0Xbf69de1d, 0Xbf6803ca, 0Xbf66175e, 0Xbf641901, 0Xbf6208da, 0Xbf5fe714, 
0Xbf5db3d7, 0Xbf5b6f51, 0Xbf5919ae, 0Xbf56b31d, 0Xbf543bce, 0Xbf51b3f3, 
0Xbf4f1bbd, 0Xbf4c7360, 0Xbf49bb13, 0Xbf46f30a, 0Xbf441b7d, 0Xbf4134a6, 
0Xbf3e3ebd, 0Xbf3b39ff, 0Xbf3826a7, 0Xbf3504f3, 0Xbf31d522, 0Xbf2e9772, 
0Xbf2b4c25, 0Xbf27f37c, 0Xbf248dbb, 0Xbf211b24, 0Xbf1d9bfe, 0Xbf1a108d, 
0Xbf167918, 0Xbf12d5e8, 0Xbf0f2744, 0Xbf0b6d77, 0Xbf07a8ca, 0Xbf03d989, 
0Xbf000000, 0Xbef838f7, 0Xbef05e94, 0Xbee87171, 0Xbee0722f, 0Xbed8616c, 
0Xbed03fc9, 0Xbec80de9, 0Xbebfcc6f, 0Xbeb77c01, 0Xbeaf1d44, 0Xbea6b0df, 
0Xbe9e377a, 0Xbe95b1be, 0Xbe8d2057, 0Xbe8483ee, 0Xbe77ba60, 0Xbe665992, 
0Xbe54e6cd, 0Xbe43636f, 0Xbe31d0d4, 0Xbe20305b, 0Xbe0e8365, 0Xbdf996a2, 
0Xbdd61305, 0Xbdb27eb6, 0Xbd8edc7b, 0Xbd565e3a, 0Xbd0ef2c6, 0Xbc8ef859, 
0X00000000, 
};

static unsigned int g_acs[204] = {
0X40490fdb, 0X404000df, 0X403c3d91, 0X40395882, 0X4036e62c, 0X4034bcf2, 
0X4032c780, 0X4030f930, 0X402f49c2, 0X402db37e, 0X402c323b, 0X402ac2d5, 
0X402962da, 0X4028105d, 0X4026c9c9, 0X40258dd4, 0X40245b6a, 0X402331a1, 
0X40220faf, 0X4020f4ea, 0X401fe0bb, 0X401ed29f, 0X401dca22, 0X401cc6dc, 
0X401bc873, 0X401ace93, 0X4019d8f4, 0X4018e750, 0X4017f96d, 0X40170f11, 
0X4016280a, 0X4015442a, 0X40146345, 0X40138534, 0X4012a9d2, 0X4011d0fe, 
0X4010fa96, 0X4010267f, 0X400f549c, 0X400e84d3, 0X400db70d, 0X400ceb32, 
0X400c212e, 0X400b58eb, 0X400a9258, 0X4009cd62, 0X400909f8, 0X4008480a, 
0X40078788, 0X4006c865, 0X40060a92, 0X40054e01, 0X400492a7, 0X4003d878, 
0X40031f66, 0X40026769, 0X4001b075, 0X4000fa7f, 0X4000457f, 0X3fff22d4, 
0X3ffdbc70, 0X3ffc57c0, 0X3ffaf4b3, 0X3ff99339, 0X3ff83342, 0X3ff6d4be, 
0X3ff577a0, 0X3ff41bd9, 0X3ff2c15c, 0X3ff16819, 0X3ff01006, 0X3feeb914, 
0X3fed6338, 0X3fec0e66, 0X3feaba91, 0X3fe967ae, 0X3fe815b3, 0X3fe6c493, 
0X3fe57445, 0X3fe424be, 0X3fe2d5f3, 0X3fe187db, 0X3fe03a6b, 0X3fdeed9a, 
0X3fdda15e, 0X3fdc55ad, 0X3fdb0a7e, 0X3fd9bfc9, 0X3fd87583, 0X3fd72ba5, 
0X3fd5e224, 0X3fd498f8, 0X3fd35019, 0X3fd2077e, 0X3fd0bf1e, 0X3fcf76f0, 
0X3fce2eec, 0X3fcce70b, 0X3fcb9f42, 0X3fca578a, 0X3fc90fdb, 0X3fc7c82b, 
0X3fc68073, 0X3fc538ab, 0X3fc3f0c9, 0X3fc2a8c5, 0X3fc16098, 0X3fc01837, 
0X3fbecf9c, 0X3fbd86bd, 0X3fbc3d91, 0X3fbaf411, 0X3fb9aa32, 0X3fb85fec, 
0X3fb71537, 0X3fb5ca08, 0X3fb47e58, 0X3fb3321c, 0X3fb1e54a, 0X3fb097da, 
0X3faf49c2, 0X3fadfaf7, 0X3facab70, 0X3fab5b22, 0X3faa0a03, 0X3fa8b807, 
0X3fa76524, 0X3fa61150, 0X3fa4bc7d, 0X3fa366a1, 0X3fa20faf, 0X3fa0b79c, 
0X3f9f5e5a, 0X3f9e03dc, 0X3f9ca815, 0X3f9b4af7, 0X3f99ec74, 0X3f988c7d, 
0X3f972b02, 0X3f95c7f5, 0X3f946345, 0X3f92fce1, 0X3f9194b8, 0X3f902ab7, 
0X3f8ebecc, 0X3f8d50e3, 0X3f8be0e8, 0X3f8a6ec6, 0X3f88fa67, 0X3f8783b2, 
0X3f860a92, 0X3f848eeb, 0X3f8310a4, 0X3f818fa1, 0X3f800bc5, 0X3f7d09e3, 
0X3f79f60a, 0X3f76dbbe, 0X3f73bab4, 0X3f7092a3, 0X3f6d6338, 0X3f6a2c1f, 
0X3f66ecfc, 0X3f63a570, 0X3f605512, 0X3f5cfb74, 0X3f599821, 0X3f562a9a, 
0X3f52b256, 0X3f4f2ec3, 0X3f4b9f42, 0X3f480327, 0X3f4459b8, 0X3f40a229, 
0X3f3cdb9c, 0X3f39051d, 0X3f351d9f, 0X3f3123f9, 0X3f2d16e4, 0X3f28f4ee, 
0X3f24bc7d, 0X3f206bc1, 0X3f1c00ad, 0X3f1778e8, 0X3f12d1c1, 0X3f0e0819, 
0X3f091846, 0X3f03fdf8, 0X3efd6801, 0X3ef26831, 0X3ee6ecfc, 0X3edae2e3, 
0X3ece30c5, 0X3ec0b556, 0X3eb242d1, 0X3ea29748, 0X3e914d76, 0X3e7b7587, 
0X3e4d2494, 0X3e10efb9, 0X00000000, 
};








void DGX_MakeCosSinTable()
{
	int i;

	FLOAT	Cos, Sin, Acs;
	DOUBLE	Rad, v;


	for(i=0; i<361; ++i)
	{
		Rad = i * DGX_PI /180.;
		Cos = (float)cos(Rad);

		if(-0.000005 <= Cos && Cos <= 0.000005)
			Cos = 0;

		else if(-0.999995 >= Cos)
			Cos = -1;

		else if(0.999995 <= Cos)
			Cos = 1;


		g_cos[i] = *((unsigned int*)&Cos);
	}



	for(i=0; i<361; ++i)
	{
		Rad = i * DGX_PI /180.;
		Sin = (float)sin(Rad);

		if(-0.000005 <= Sin && Sin <= 0.000005)
			Sin = 0;

		else if(-0.999995 >= Sin)
			Sin = -1;

		else if(0.999995 <= Sin)
			Sin = 1;


		g_sin[i] = *((unsigned int*)&Sin);
	}


	for(i=0; i<=200; ++i)
	{
		v = (i-100.)/100.0;

		if(-0.999995 > v)
			Acs = (float)DGX_PI;

		else if(0.0 == v)
			Acs = (float)(DGX_PI/2.);

		else if(0.999995 <= v)
			Acs = 0.F;

		else
			Acs = (float)acos(v);


		g_acs[i] = *((unsigned int*)&Acs);
	}
}


void PrintMathTable()
{
	int i;
	FILE* fp = NULL;

	unsigned int v;

	fp = fopen("Math.txt", "wt");

	fprintf(fp, "static	unsigned int g_cos[364] = {\n");

	for(i=0; i<361; ++i)
	{
		v = *((unsigned int*)&g_cos[i]);

		if(v)
			fprintf(fp, "0X%x, ", v);
		else
			fprintf(fp, "0X0000000%x, ", v);

		if(0 == (i+1)%6)
			fprintf(fp, "\n");
	}

	fprintf(fp, "\n};\n\n");



	fprintf(fp, "static	unsigned int g_sin[364] = {\n");

	for(i=0; i<361; ++i)
	{
		v = *((unsigned int*)&g_sin[i]);

		if(v)
			fprintf(fp, "0X%x, ", v);
		else
			fprintf(fp, "0X0000000%x, ", v);
		
		if(0 == (i+1)%6)
			fprintf(fp, "\n");
	}

	fprintf(fp, "\n};\n\n");



	fprintf(fp, "static unsigned int g_acs[204] = {\n");


	for(i=0; i<=200; ++i)
	{
		v = *((unsigned int*)&g_acs[i]);

		if(v)
			fprintf(fp, "0X%x, ", v);
		else
			fprintf(fp, "0X0000000%x, ", v);
		
		if(0 == (i+1)%6)
			fprintf(fp, "\n");
	}


	fprintf(fp, "\n};\n\n");

	fclose(fp);
}


FLOAT DGX_Cos(FLOAT Rad)
{
	FLOAT t = 0;
	FLOAT w = 0;
	INT	  R = 0;
	FLOAT D = DGXToDegree(Rad);

	FLOAT v0 = 0.0F, v1 = 0.0F;

	R = (INT)(D/360.F);
	D = D - R * 360;

	if(D<0)	D += 360.F;

	R = (INT)(D);
	w = D - R;

	v0= *((FLOAT*)(g_cos +R   ));
	v1= *((FLOAT*)(g_cos + R+1));

	t = (1.F - w) * v0 + w * v1;
	return (t);
}


FLOAT DGX_Sin(FLOAT Rad)
{
	FLOAT t = 0;
	FLOAT w = 0;
	INT	  R = 0;
	FLOAT D = DGXToDegree(Rad);

	FLOAT v0 = 0.0F, v1 = 0.0F;

	R = (INT)(D/360.F);
	D = D - R * 360;

	if(D<0)	D += 360.F;

	R = (INT)(D);
	w = D - R;

	v0= *((FLOAT*)(g_sin + R  ));
	v1= *((FLOAT*)(g_sin + R+1));

	t = (1.F - w) * v0 + w * v1;
	return (t);
}


FLOAT DGX_Acos(FLOAT v)
{
	FLOAT t = 0;
	FLOAT w = 0;

	INT   n = 0;
	FLOAT v0 = 0.0F, v1 = 0.0F;


	// boundary
	if(-0.999995 > v)
		return (float)DGX_PI;

	else if(0.0 == v)
		return (float)(DGX_PI/2.);

	else if(0.999995 <= v)
		return 0.F;


	t = v * 100.F + 101.F;
	n = int ( t );

	w = t-n;

	v0= *((FLOAT*)(g_acs + n-1));
	v1= *((FLOAT*)(g_acs + n  ));

	t = (1.F - w) * v0 + w * v1;
	return (t);
}





int main(int argc, char** argv)
{
	int i;

	DGX_MakeCosSinTable();
	PrintMathTable();

	printf("Cosine Table----------------------------------\n");

	for(i=0; i<361; ++i)
	{
		float v = DGXToRadian(i);

		FLOAT t1 = (float)sin(v);
		FLOAT t2 = DGX_Sin(v);
		FLOAT t = t1 - t2;

		printf("%12.6f %12.6f  %12.6f\n", t1, t2, t);
	}

	printf("\n\nSine Table----------------------------------\n");


	for(i=0; i<361; ++i)
	{
		float v = DGXToRadian(i);

		FLOAT t1 = (float)cos(v);
		FLOAT t2 = DGX_Cos(v);
		FLOAT t = t1 - t2;

		printf("%12.6f %12.6f  %12.6f\n", t1, t2, t);
	}

	printf("\n\nArcCosine Table----------------------------------\n");

	for(i=0; i<200; ++i)
	{
		float v = (i-100.F)/100.F;

		FLOAT t1= (float)acos(v);
		FLOAT t2= DGX_Acos(v);
		FLOAT t = t1 - t2;

		printf("%12.6f %12.6f  %12.6f\n", t1, t2, t);
	}

	printf("\n\n----------------------------------\n");


	unsigned int c = 0X7F7FFFFF;

	FLOAT t =*((float*)(&c));
	
	t =3.40282347e+38F;

	c  =*((unsigned int*)(&t));


	if( t == 3.402823466e+38F)
        printf("%f\n", t);
	
	return 0;
}


