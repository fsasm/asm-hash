/*
 * whirlpool_table32.s
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-17
 */

.section .rodata
.align 4
whirlpool_round_const:
	.long 0x87B8014F
	.long 0x1823C6E8
	.long 0x796F9152
	.long 0x36A6D2F5
	.long 0xA30C7B35
	.long 0x60BC9B8E
	.long 0x2E4BFE57
	.long 0x1DE0D7C2 /*  4 */
	.long 0x9FF04ADA
	.long 0x157737E5
	.long 0xB1A06B85
	.long 0x58C9290A
	.long 0xCB3E0567
	.long 0xBD5D10F4
	.long 0xA77D95D8
	.long 0xE427418B /*  8 */
	.long 0xDD17479E
	.long 0xFBEE7C66
	.long 0xAD5A8333
	.long 0xCA2DBF07 /* 10 */

whirlpool_table0:	/* table 1 */
	.long 0xC07830D8
	.long 0x18186018
	.long 0x05AF4626
	.long 0x23238C23
	.long 0x7EF991B8
	.long 0xC6C63FC6
	.long 0x136FCDFB
	.long 0xE8E887E8 /* 4 */
	.long 0x4CA113CB
	.long 0x87872687
	.long 0xA9626D11
	.long 0xB8B8DAB8
	.long 0x08050209
	.long 0x01010401
	.long 0x426E9E0D
	.long 0x4F4F214F /* 8 */
	.long 0xADEE6C9B
	.long 0x3636D836
	.long 0x590451FF
	.long 0xA6A6A2A6
	.long 0xDEBDB90C
	.long 0xD2D26FD2
	.long 0xFB06F70E
	.long 0xF5F5F3F5 /* 12 */
	.long 0xEF80F296
	.long 0x7979F979
	.long 0x5FCEDE30
	.long 0x6F6FA16F
	.long 0xFCEF3F6D
	.long 0x91917E91
	.long 0xAA07A4F8
	.long 0x52525552 /* 16 */
	.long 0x27FDC047
	.long 0x60609D60
	.long 0x89766535
	.long 0xBCBCCABC
	.long 0xACCD2B37
	.long 0x9B9B569B
	.long 0x048C018A
	.long 0x8E8E028E /* 20 */
	.long 0x71155BD2
	.long 0xA3A3B6A3
	.long 0x603C186C
	.long 0x0C0C300C
	.long 0xFF8AF684
	.long 0x7B7BF17B
	.long 0xB5E16A80
	.long 0x3535D435 /* 24 */
	.long 0xE8693AF5
	.long 0x1D1D741D
	.long 0x5347DDB3
	.long 0xE0E0A7E0
	.long 0xF6ACB321
	.long 0xD7D77BD7
	.long 0x5EED999C
	.long 0xC2C22FC2 /* 28 */
	.long 0x6D965C43
	.long 0x2E2EB82E
	.long 0x627A9629
	.long 0x4B4B314B
	.long 0xA321E15D
	.long 0xFEFEDFFE
	.long 0x8216AED5
	.long 0x57574157 /* 32 */
	.long 0xA8412ABD
	.long 0x15155415
	.long 0x9FB6EEE8
	.long 0x7777C177
	.long 0xA5EB6E92
	.long 0x3737DC37
	.long 0x7B56D79E
	.long 0xE5E5B3E5 /* 36 */
	.long 0x8CD92313
	.long 0x9F9F469F
	.long 0xD317FD23
	.long 0xF0F0E7F0
	.long 0x6A7F9420
	.long 0x4A4A354A
	.long 0x9E95A944
	.long 0xDADA4FDA /* 40 */
	.long 0xFA25B0A2
	.long 0x58587D58
	.long 0x06CA8FCF
	.long 0xC9C903C9
	.long 0x558D527C
	.long 0x2929A429
	.long 0x5022145A
	.long 0x0A0A280A /* 44 */
	.long 0xE14F7F50
	.long 0xB1B1FEB1
	.long 0x691A5DC9
	.long 0xA0A0BAA0
	.long 0x7FDAD614
	.long 0x6B6BB16B
	.long 0x5CAB17D9
	.long 0x85852E85 /* 48 */
	.long 0x8173673C
	.long 0xBDBDCEBD
	.long 0xD234BA8F
	.long 0x5D5D695D
	.long 0x80502090
	.long 0x10104010
	.long 0xF303F507
	.long 0xF4F4F7F4 /* 52 */
	.long 0x16C08BDD
	.long 0xCBCB0BCB
	.long 0xEDC67CD3
	.long 0x3E3EF83E
	.long 0x28110A2D
	.long 0x05051405
	.long 0x1FE6CE78
	.long 0x67678167 /* 56 */
	.long 0x7353D597
	.long 0xE4E4B7E4
	.long 0x25BB4E02
	.long 0x27279C27
	.long 0x32588273
	.long 0x41411941
	.long 0x2C9D0BA7
	.long 0x8B8B168B /* 60 */
	.long 0x510153F6
	.long 0xA7A7A6A7
	.long 0xCF94FAB2
	.long 0x7D7DE97D
	.long 0xDCFB3749
	.long 0x95956E95
	.long 0x8E9FAD56
	.long 0xD8D847D8 /* 64 */
	.long 0x8B30EB70
	.long 0xFBFBCBFB
	.long 0x2371C1CD
	.long 0xEEEE9FEE
	.long 0xC791F8BB
	.long 0x7C7CED7C
	.long 0x17E3CC71
	.long 0x66668566 /* 68 */
	.long 0xA68EA77B
	.long 0xDDDD53DD
	.long 0xB84B2EAF
	.long 0x17175C17
	.long 0x02468E45
	.long 0x47470147
	.long 0x84DC211A
	.long 0x9E9E429E /* 72 */
	.long 0x1EC589D4
	.long 0xCACA0FCA
	.long 0x75995A58
	.long 0x2D2DB42D
	.long 0x9179632E
	.long 0xBFBFC6BF
	.long 0x381B0E3F
	.long 0x07071C07 /* 76 */
	.long 0x012347AC
	.long 0xADAD8EAD
	.long 0xEA2FB4B0
	.long 0x5A5A755A
	.long 0x6CB51BEF
	.long 0x83833683
	.long 0x85FF66B6
	.long 0x3333CC33 /* 80 */
	.long 0x3FF2C65C
	.long 0x63639163
	.long 0x100A0412
	.long 0x02020802
	.long 0x39384993
	.long 0xAAAA92AA
	.long 0xAFA8E2DE
	.long 0x7171D971 /* 84 */
	.long 0x0ECF8DC6
	.long 0xC8C807C8
	.long 0xC87D32D1
	.long 0x19196419
	.long 0x7270923B
	.long 0x49493949
	.long 0x869AAF5F
	.long 0xD9D943D9 /* 88 */
	.long 0xC31DF931
	.long 0xF2F2EFF2
	.long 0x4B48DBA8
	.long 0xE3E3ABE3
	.long 0xE22AB6B9
	.long 0x5B5B715B
	.long 0x34920DBC
	.long 0x88881A88 /* 92 */
	.long 0xA4C8293E
	.long 0x9A9A529A
	.long 0x2DBE4C0B
	.long 0x26269826
	.long 0x8DFA64BF
	.long 0x3232C832
	.long 0xE94A7D59
	.long 0xB0B0FAB0 /* 96 */
	.long 0x1B6ACFF2
	.long 0xE9E983E9
	.long 0x78331E77
	.long 0x0F0F3C0F
	.long 0xE6A6B733
	.long 0xD5D573D5
	.long 0x74BA1DF4
	.long 0x80803A80 /* 100 */
	.long 0x997C6127
	.long 0xBEBEC2BE
	.long 0x26DE87EB
	.long 0xCDCD13CD
	.long 0xBDE46889
	.long 0x3434D034
	.long 0x7A759032
	.long 0x48483D48 /* 104 */
	.long 0xAB24E354
	.long 0xFFFFDBFF
	.long 0xF78FF48D
	.long 0x7A7AF57A
	.long 0xF4EA3D64
	.long 0x90907A90
	.long 0xC23EBE9D
	.long 0x5F5F615F /* 108 */
	.long 0x1DA0403D
	.long 0x20208020
	.long 0x67D5D00F
	.long 0x6868BD68
	.long 0xD07234CA
	.long 0x1A1A681A
	.long 0x192C41B7
	.long 0xAEAE82AE /* 112 */
	.long 0xC95E757D
	.long 0xB4B4EAB4
	.long 0x9A19A8CE
	.long 0x54544D54
	.long 0xECE53B7F
	.long 0x93937693
	.long 0x0DAA442F
	.long 0x22228822 /* 116 */
	.long 0x07E9C863
	.long 0x64648D64
	.long 0xDB12FF2A
	.long 0xF1F1E3F1
	.long 0xBFA2E6CC
	.long 0x7373D173
	.long 0x905A2482
	.long 0x12124812 /* 120 */
	.long 0x3A5D807A
	.long 0x40401D40
	.long 0x40281048
	.long 0x08082008
	.long 0x56E89B95
	.long 0xC3C32BC3
	.long 0x337BC5DF
	.long 0xECEC97EC /* 124 */
	.long 0x9690AB4D
	.long 0xDBDB4BDB
	.long 0x611F5FC0
	.long 0xA1A1BEA1
	.long 0x1C830791
	.long 0x8D8D0E8D
	.long 0xF5C97AC8
	.long 0x3D3DF43D /* 128 */
	.long 0xCCF1335B
	.long 0x97976697
	.long 0x00000000
	.long 0x00000000
	.long 0x36D483F9
	.long 0xCFCF1BCF
	.long 0x4587566E
	.long 0x2B2BAC2B /* 132 */
	.long 0x97B3ECE1
	.long 0x7676C576
	.long 0x64B019E6
	.long 0x82823282
	.long 0xFEA9B128
	.long 0xD6D67FD6
	.long 0xD87736C3
	.long 0x1B1B6C1B /* 136 */
	.long 0xC15B7774
	.long 0xB5B5EEB5
	.long 0x112943BE
	.long 0xAFAF86AF
	.long 0x77DFD41D
	.long 0x6A6AB56A
	.long 0xBA0DA0EA
	.long 0x50505D50 /* 140 */
	.long 0x124C8A57
	.long 0x45450945
	.long 0xCB18FB38
	.long 0xF3F3EBF3
	.long 0x9DF060AD
	.long 0x3030C030
	.long 0x2B74C3C4
	.long 0xEFEF9BEF /* 144 */
	.long 0xE5C37EDA
	.long 0x3F3FFC3F
	.long 0x921CAAC7
	.long 0x55554955
	.long 0x791059DB
	.long 0xA2A2B2A2
	.long 0x0365C9E9
	.long 0xEAEA8FEA /* 148 */
	.long 0x0FECCA6A
	.long 0x65658965
	.long 0xB9686903
	.long 0xBABAD2BA
	.long 0x65935E4A
	.long 0x2F2FBC2F
	.long 0x4EE79D8E
	.long 0xC0C027C0 /* 152 */
	.long 0xBE81A160
	.long 0xDEDE5FDE
	.long 0xE06C38FC
	.long 0x1C1C701C
	.long 0xBB2EE746
	.long 0xFDFDD3FD
	.long 0x52649A1F
	.long 0x4D4D294D /* 156 */
	.long 0xE4E03976
	.long 0x92927292
	.long 0x8FBCEAFA
	.long 0x7575C975
	.long 0x301E0C36
	.long 0x06061806
	.long 0x249809AE
	.long 0x8A8A128A /* 160 */
	.long 0xF940794B
	.long 0xB2B2F2B2
	.long 0x6359D185
	.long 0xE6E6BFE6
	.long 0x70361C7E
	.long 0x0E0E380E
	.long 0xF8633EE7
	.long 0x1F1F7C1F /* 164 */
	.long 0x37F7C455
	.long 0x62629562
	.long 0xEEA3B53A
	.long 0xD4D477D4
	.long 0x29324D81
	.long 0xA8A89AA8
	.long 0xC4F43152
	.long 0x96966296 /* 168 */
	.long 0x9B3AEF62
	.long 0xF9F9C3F9
	.long 0x66F697A3
	.long 0xC5C533C5
	.long 0x35B14A10
	.long 0x25259425
	.long 0xF220B2AB
	.long 0x59597959 /* 172 */
	.long 0x54AE15D0
	.long 0x84842A84
	.long 0xB7A7E4C5
	.long 0x7272D572
	.long 0xD5DD72EC
	.long 0x3939E439
	.long 0x5A619816
	.long 0x4C4C2D4C /* 176 */
	.long 0xCA3BBC94
	.long 0x5E5E655E
	.long 0xE785F09F
	.long 0x7878FD78
	.long 0xDDD870E5
	.long 0x3838E038
	.long 0x14860598
	.long 0x8C8C0A8C /* 180 */
	.long 0xC6B2BF17
	.long 0xD1D163D1
	.long 0x410B57E4
	.long 0xA5A5AEA5
	.long 0x434DD9A1
	.long 0xE2E2AFE2
	.long 0x2FF8C24E
	.long 0x61619961 /* 184 */
	.long 0xF1457B42
	.long 0xB3B3F6B3
	.long 0x15A54234
	.long 0x21218421
	.long 0x94D62508
	.long 0x9C9C4A9C
	.long 0xF0663CEE
	.long 0x1E1E781E /* 188 */
	.long 0x22528661
	.long 0x43431143
	.long 0x76FC93B1
	.long 0xC7C73BC7
	.long 0xB32BE54F
	.long 0xFCFCD7FC
	.long 0x20140824
	.long 0x04041004 /* 192 */
	.long 0xB208A2E3
	.long 0x51515951
	.long 0xBCC72F25
	.long 0x99995E99
	.long 0x4FC4DA22
	.long 0x6D6DA96D
	.long 0x68391A65
	.long 0x0D0D340D /* 196 */
	.long 0x8335E979
	.long 0xFAFACFFA
	.long 0xB684A369
	.long 0xDFDF5BDF
	.long 0xD79BFCA9
	.long 0x7E7EE57E
	.long 0x3DB44819
	.long 0x24249024 /* 200 */
	.long 0xC5D776FE
	.long 0x3B3BEC3B
	.long 0x313D4B9A
	.long 0xABAB96AB
	.long 0x3ED181F0
	.long 0xCECE1FCE
	.long 0x88552299
	.long 0x11114411 /* 204 */
	.long 0x0C890383
	.long 0x8F8F068F
	.long 0x4A6B9C04
	.long 0x4E4E254E
	.long 0xD1517366
	.long 0xB7B7E6B7
	.long 0x0B60CBE0
	.long 0xEBEB8BEB /* 208 */
	.long 0xFDCC78C1
	.long 0x3C3CF03C
	.long 0x7CBF1FFD
	.long 0x81813E81
	.long 0xD4FE3540
	.long 0x94946A94
	.long 0xEB0CF31C
	.long 0xF7F7FBF7 /* 212 */
	.long 0xA1676F18
	.long 0xB9B9DEB9
	.long 0x985F268B
	.long 0x13134C13
	.long 0x7D9C5851
	.long 0x2C2CB02C
	.long 0xD6B8BB05
	.long 0xD3D36BD3 /* 216 */
	.long 0x6B5CD38C
	.long 0xE7E7BBE7
	.long 0x57CBDC39
	.long 0x6E6EA56E
	.long 0x6EF395AA
	.long 0xC4C437C4
	.long 0x180F061B
	.long 0x03030C03 /* 220 */
	.long 0x8A13ACDC
	.long 0x56564556
	.long 0x1A49885E
	.long 0x44440D44
	.long 0xDF9EFEA0
	.long 0x7F7FE17F
	.long 0x21374F88
	.long 0xA9A99EA9 /* 224 */
	.long 0x4D825467
	.long 0x2A2AA82A
	.long 0xB16D6B0A
	.long 0xBBBBD6BB
	.long 0x46E29F87
	.long 0xC1C123C1
	.long 0xA202A6F1
	.long 0x53535153 /* 228 */
	.long 0xAE8BA572
	.long 0xDCDC57DC
	.long 0x58271653
	.long 0x0B0B2C0B
	.long 0x9CD32701
	.long 0x9D9D4E9D
	.long 0x47C1D82B
	.long 0x6C6CAD6C /* 232 */
	.long 0x95F562A4
	.long 0x3131C431
	.long 0x87B9E8F3
	.long 0x7474CD74
	.long 0xE309F115
	.long 0xF6F6FFF6
	.long 0x0A438C4C
	.long 0x46460546 /* 236 */
	.long 0x092645A5
	.long 0xACAC8AAC
	.long 0x3C970FB5
	.long 0x89891E89
	.long 0xA04428B4
	.long 0x14145014
	.long 0x5B42DFBA
	.long 0xE1E1A3E1 /* 240 */
	.long 0xB04E2CA6
	.long 0x16165816
	.long 0xCDD274F7
	.long 0x3A3AE83A
	.long 0x6FD0D206
	.long 0x6969B969
	.long 0x482D1241
	.long 0x09092409 /* 244 */
	.long 0xA7ADE0D7
	.long 0x7070DD70
	.long 0xD954716F
	.long 0xB6B6E2B6
	.long 0xCEB7BD1E
	.long 0xD0D067D0
	.long 0x3B7EC7D6
	.long 0xEDED93ED /* 248 */
	.long 0x2EDB85E2
	.long 0xCCCC17CC
	.long 0x2A578468
	.long 0x42421542
	.long 0xB4C22D2C
	.long 0x98985A98
	.long 0x490E55ED
	.long 0xA4A4AAA4 /* 252 */
	.long 0x5D885075
	.long 0x2828A028
	.long 0xDA31B886
	.long 0x5C5C6D5C
	.long 0x933FED6B
	.long 0xF8F8C7F8
	.long 0x44A411C2
	.long 0x86862286 /* 256 */

