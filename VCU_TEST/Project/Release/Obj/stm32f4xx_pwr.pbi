      F&�        &&'�      ''5	�    5	5::	�    :	:5;	�    ;	;&<	�    <	<[?	�    ?	?&@	�    @	@\C	�    C	C&D	�	   	 D	D\G	�
   	
 G	G'H	�   
 H	H^K	�    K	K&L	�    L	L\O	�    O	O&P	�    P	P^|	�    |	|&}	�    }	}[�	�    �	�8�	�    �	�8�	�    �	�8��<	 ���� �����	 ���� ���� ����@	 �� �*
�* ��2�"
�" ��.�� ����}	 �� �!
�! ��)� �! �����	 ���-
�- ��5�"�# ����L	 �� �+
$�+ �"�@�%�& ����P	 ��"�'
�'  ��/�'�!( ����	D		 �� �)
�)" ��1�)�#* �����	 ���(
�($ ��0�-�'. �����	 ���+�%, ���!
/�!( ��.�g1� 2 ���g1� 2 ���,
�,& ��4�8
0�8) �0�E�e1� 2 ��
�g3� 4 ���e1� 2 ��
�g3� 4 ���e3� 4 ��
�5�*6 ���e3� 4 ��
�7�-8 ���+
/�++ �"�8�g1� 2 ��
�B
0�B, �:�O�e1� 2 ���9�.: ���;�/< ���
=�0 ��%   >  +5CM\gv�����������������������������������������������������stm32f4xx_pwr.h stm32f4xx_rcc.h PWR_OFFSET CR_OFFSET DBP_BitNumber CR_DBP_BB PVDE_BitNumber CR_PVDE_BB FPDS_BitNumber CR_FPDS_BB PMODE_BitNumber CR_PMODE_BB ODEN_BitNumber CR_ODEN_BB ODSWEN_BitNumber CR_ODSWEN_BB BRE_BitNumber CSR_BRE_BB CR_DS_MASK CR_PLS_MASK CR_VOS_MASK PWR_DeInit void PWR_DeInit(void) PWR_BackupAccessCmd void PWR_BackupAccessCmd(int) NewState int PWR_PVDLevelConfig void PWR_PVDLevelConfig(int) PWR_PVDLevel PWR_PVDCmd void PWR_PVDCmd(int) PWR_BackupRegulatorCmd void PWR_BackupRegulatorCmd(int) PWR_MainRegulatorModeConfig void PWR_MainRegulatorModeConfig(int) PWR_Regulator_Voltage PWR_OverDriveCmd void PWR_OverDriveCmd(int) PWR_OverDriveSWCmd void PWR_OverDriveSWCmd(int) PWR_UnderDriveCmd void PWR_UnderDriveCmd(int) PWR_FlashPowerDownCmd void PWR_FlashPowerDownCmd(int) PWR_EnterSTOPMode void PWR_EnterSTOPMode(int, int) PWR_Regulator PWR_STOPEntry __WFI int __WFI(void) __WFE int __WFE(void) PWR_EnterUnderDriveSTOPMode void PWR_EnterUnderDriveSTOPMode(int, int) PWR_EnterSTANDBYMode void PWR_EnterSTANDBYMode(void) PWR_GetFlagStatus int PWR_GetFlagStatus(int) PWR_ClearFlag void PWR_ClearFlag(int) PWR_FLAG    1 )P{���������������������������	�	�
�
�
�
������������� c:stm32f4xx_pwr.c@2080@macro@PWR_OFFSET c:stm32f4xx_pwr.c@2206@macro@CR_OFFSET c:stm32f4xx_pwr.c@2260@macro@DBP_BitNumber c:stm32f4xx_pwr.c@2299@macro@CR_DBP_BB c:stm32f4xx_pwr.c@2431@macro@PVDE_BitNumber c:stm32f4xx_pwr.c@2470@macro@CR_PVDE_BB c:stm32f4xx_pwr.c@2603@macro@FPDS_BitNumber c:stm32f4xx_pwr.c@2642@macro@CR_FPDS_BB c:stm32f4xx_pwr.c@2776@macro@PMODE_BitNumber c:stm32f4xx_pwr.c@2816@macro@CR_PMODE_BB c:stm32f4xx_pwr.c@2951@macro@ODEN_BitNumber c:stm32f4xx_pwr.c@2990@macro@CR_ODEN_BB c:stm32f4xx_pwr.c@3125@macro@ODSWEN_BitNumber c:stm32f4xx_pwr.c@3164@macro@CR_ODSWEN_BB c:stm32f4xx_pwr.c@5744@macro@BRE_BitNumber c:stm32f4xx_pwr.c@5783@macro@CSR_BRE_BB c:stm32f4xx_pwr.c@5981@macro@CR_DS_MASK c:stm32f4xx_pwr.c@6038@macro@CR_PLS_MASK c:stm32f4xx_pwr.c@6095@macro@CR_VOS_MASK c:@F@PWR_DeInit c:@F@PWR_BackupAccessCmd c:stm32f4xx_pwr.c@8110@F@PWR_BackupAccessCmd@NewState c:@F@PWR_PVDLevelConfig c:stm32f4xx_pwr.c@9891@F@PWR_PVDLevelConfig@PWR_PVDLevel c:@F@PWR_PVDCmd c:stm32f4xx_pwr.c@10469@F@PWR_PVDCmd@NewState c:@F@PWR_BackupRegulatorCmd c:stm32f4xx_pwr.c@18897@F@PWR_BackupRegulatorCmd@NewState c:@F@PWR_MainRegulatorModeConfig c:stm32f4xx_pwr.c@20095@F@PWR_MainRegulatorModeConfig@PWR_Regulator_Voltage c:@F@PWR_OverDriveCmd c:stm32f4xx_pwr.c@21390@F@PWR_OverDriveCmd@NewState c:@F@PWR_OverDriveSWCmd c:stm32f4xx_pwr.c@21966@F@PWR_OverDriveSWCmd@NewState c:@F@PWR_UnderDriveCmd c:stm32f4xx_pwr.c@23120@F@PWR_UnderDriveCmd@NewState c:@F@PWR_FlashPowerDownCmd c:stm32f4xx_pwr.c@27577@F@PWR_FlashPowerDownCmd@NewState c:@F@PWR_EnterSTOPMode c:stm32f4xx_pwr.c@34876@F@PWR_EnterSTOPMode@PWR_Regulator c:stm32f4xx_pwr.c@34900@F@PWR_EnterSTOPMode@PWR_STOPEntry c:@F@PWR_EnterUnderDriveSTOPMode c:stm32f4xx_pwr.c@37563@F@PWR_EnterUnderDriveSTOPMode@PWR_Regulator c:stm32f4xx_pwr.c@37587@F@PWR_EnterUnderDriveSTOPMode@PWR_STOPEntry c:@F@PWR_EnterSTANDBYMode c:@F@PWR_GetFlagStatus c:@F@PWR_ClearFlag c:stm32f4xx_pwr.c@42634@F@PWR_ClearFlag@PWR_FLAG     F<invalid loc> C:\Users\ZH\Desktop\std_stm32\FWLIB\src\stm32f4xx_pwr.c 