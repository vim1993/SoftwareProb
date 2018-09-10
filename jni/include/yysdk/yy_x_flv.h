#ifndef YY_X_FLV_H
#define YY_X_FLV_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
#include "yy_f_alloc.h"
#include "yy_f_buffer.h"
#include "yy_e_http.h"
#include "yy_f_file_obj.h"

/* ����FLV�ļ����� */

/* ָ��ԭ�����뷽ʽ����ѹջ�������µĶ��뷽ʽ����Ϊһ���ֽڶ��� */
#pragma pack(push,1)

/* �����ļ�ͷ��Ϣ */
typedef struct yy_x_flv_fileheader_s
{
	yy_p_uint8 signature[3];	    /* FLV */
	yy_p_uint8 version;	            //�汾�� 0x01-now
	yy_p_uint8 flag_video:1;	    //��Ƶ��־
	yy_p_uint8 flag_b1:1;		    //����
	yy_p_uint8 flag_audio:1;	    //��Ƶ��־
	yy_p_uint8 flag_b5:5;		    //����	
	yy_p_uint32 data_offset;	    //The DataOffset field usually has a value of 9 for FLV version 1. This field is present to accommodate larger headers in future versions.
}yy_x_flv_fileheader_t;
typedef struct yy_x_flv_tagheader_s
{	
	yy_p_uint32 pre_tag_size;	    //ǰһ��tag�ĳ���,�����һ��tag����0
	yy_p_uint8 type;			    //* 8 -- ��Ƶtag * 9 -- ��Ƶtag * 18 -- �ű�tag
	yy_p_uint8 data_size[3];	    //���������� 3bytes 
	yy_p_uint8 timestamp[3];		//ʱ��� 3bytes ��λ����
	yy_p_uint8 timestamp_extended;	//��չʱ��� 1byte ��Ϊʱ����ĸ�λ
	yy_p_uint8 stream_id[3];		//streamsID 3bytes
	
}yy_x_flv_tagheader_t;

/*
SoundFormat
0 = Linear PCM, platform endian
1 = ADPCM
2 = MP3
3 = Linear PCM, little endian
4 = Nellymoser 16-kHz mono
5 = Nellymoser 8-kHz mono
6 = Nellymoser
7 = G.711 A-law logarithmic PCM
8 = G.711 mu-law logarithmic PCM
9 = reserved
10 = AAC
11 = Speex
14 = MP3 8-Khz
15 = Device-specific sound
Format of SoundData
Formats 7, 8, 14, and 15 are
reserved for internal use
AAC is supported in Flash
Player 9,0,115,0 and higher.
Speex is supported in Flash
Player 10 and higher.
SoundRate UB[2]
0 = 5.5-kHz
1 = 11-kHz
2 = 22-kHz
3 = 44-kHz
Sampling rate
For AAC: always 3
SoundSize UB[1]
0 = snd8Bit
1 = snd16Bit
Size of each sample. This
parameter only pertains to
uncompressed formats.
Compressed formats always
decode to 16 bits internally.
0 = snd8Bit
1 = snd16Bit
*/

/* ����ļ�ͷ��0x08��soundFormat = 10���ͻ���һ���ֽڣ�����Ƶ������Ϣ */
/* audio_tag_data�ṹ��,λ��tag_header���� */
typedef struct yy_x_flv_tag_audiodata_h_s
{
	yy_p_uint8 sound_type:1;			/* ��Ƶ���ͣ�0 = mono��1 = stereo */		
	yy_p_uint8 sound_size:1;			/* �������ȣ�0 = 8bits��1 = 16bits */		
	yy_p_uint8 sound_rate:2;			/* ��5-6λ����ֵ��ʾ�����ʣ�0 = 5.5 kHz��1 = 11 kHz��2 = 22 kHz��3 = 44 kHz */	
	yy_p_uint8 sound_format:4;			/* ��Ƶ���ݸ�ʽ */
}yy_x_flv_tag_audiodata_h_t;
/*
FrameType UB[4] 1: keyframe (for AVC, a seekable
frame)
2: inter frame (for AVC, a nonseekable
frame)
3: disposable inter frame (H.263
only)
4: generated keyframe (reserved for
server use only)
5: video info/command frame
CodecID UB[4] 1: JPEG (currently unused)
2: Sorenson H.263
3: Screen video
4: On2 VP6
5: On2 VP6 with alpha channel
6: Screen video version 2
7: AVC
VideoData If CodecID == 2
H263VIDEOPACKET
If CodecID == 3
SCREENVIDEOPACKET
If CodecID == 4
VP6FLVVIDEOPACKET
If CodecID == 5
VP6FLVALPHAVIDEOPACKET
If CodecID == 6
SCREENV2VIDEOPACKET
if CodecID == 7
AVCVIDEOPACKET
Video frame payload or UI8
(see note fo
*/

/* video_tag_data�ṹ��,λ��tag_header���棬���Codec_ID = 7,����4���ֽڣ������ؼ�֡����Ϣ */
typedef struct yy_x_flv_tag_videodata_h_s
{
	yy_p_uint8 codec_id:4;				/* ��Ƶ����ID */
	yy_p_uint8 frame_type:4;			/* ֡���� */ 	
}yy_x_flv_tag_videodata_h_t;
/*
AVCPacketType UI8 0: AVC sequence header
1: AVC NALU
2: AVC end of sequence (lower level NALU
sequence ender is not required or supported)
CompositionTime SI24 if AVCPacketType == 1
Composition time offset
else
0
Data UI8[n] if AVCPacketType == 0
AVCDecoderConfigurationRecord
else if AVCPacketType == 1
One or more NALUs (can be individual
slices per FLV packets; that is, full frames
are not strictly required)
else if AVCPacketType == 2
Empty
*/

/* �ؼ�֡�ṹ�� */
typedef struct yy_x_flv_tag_avcvideopacket_s{
    yy_p_uint8 avc_packet_type;			/* �ؼ�֡��־ */
    yy_p_uint8 composition_time[3];		
}yy_x_flv_tag_avcvideopacket_t;

/* �鿴data�������Ƿ���ڹؼ�֡����Ϣ */
extern int yy_x_flv_is_h264_keyframe( const char * data, size_t len );

/* �鿴data�������Ƿ����sps��pps��Ϣ����������Ϣ�ǽ������������Ϣ */
extern int yy_x_flv_is_h264_spspps( const char * data, size_t len );

/* �鿴data�������Ƿ���ڽ�����Ƶ����Ϣ */
extern int yy_x_flv_is_audio_meta( const char * data, size_t len );

/* ��ȡtag_header�ṹ���е�tag_size�ֶ�+tag_header�ṹ���С,��tag_size */
extern yy_p_uint32 yy_x_flv_tag_size( yy_x_flv_tagheader_t * tagh );

/* ��������tag_header�ṹ����data_size�ֶΣ�������data���ݵĳ��� */
extern void yy_x_flv_set_data_size( yy_x_flv_tagheader_t * tagh, yy_p_uint32 data_size );

/* ��������tag_header�ṹ����timestamp�ֶκ�timestamp_extended�ֶΣ�������ʱ�������չʱ���  */
extern void yy_x_flv_set_data_timestamp( yy_x_flv_tagheader_t * tagh, yy_p_uint32 timestamp );

/* ��ȡ�ļ���buf������buf��������������д�뵽buffer��,���FLV�ļ�����ȡFLVͷ�������264�ļ���ͬʱ��ȡ264 SPSPPS */
extern int yy_x_flv_file_get_metahead( yy_p_handle_t fd, yy_f_buffer_t * meta );

/* ��ȡ�ļ���buf������buf��������������д�뵽buffer��,���FLV�ļ�����ȡFLVͷ�������264�ļ���ͬʱ��ȡ264 SPSPPS */
extern int yy_x_flv_file_get_metahead2(char * file_cache, yy_p_off_t file_pos, yy_f_buffer_t * meta);

/* ��ȡ��ȡ��flv�ļ�����Ч���ݳ��� */
extern int yy_x_flv_file_parse_meta_len( yy_p_handle_t fd );

/*���ҵ�һ��H264�Ĺؼ�֡*/
extern yy_p_off_t yy_x_flv_file_find_keyframe( yy_p_handle_t fd );

/* ��ȡ��һ�γ���frame_type��tag��λ�� */
extern yy_p_off_t yy_x_flv_file_find_keyframe2( yy_f_file_obj_t * f );

/* ��ָ����posλ�ÿ�ʼ��ȡ��һ�γ���frame_type��tag��λ�� */
extern yy_p_off_t yy_x_flv_file_find_keyframe2_by_pos( yy_f_file_obj_t * f, yy_p_off_t pos );

/*����flvheader,onmetadata,h264sps���һ����Ч���ݰ���λ��*/
extern yy_p_off_t yy_x_flv_file_first_data_tag( yy_p_handle_t fd );

/* ��ȡ��һ�γ�����Ƶ������Ƶ������Ϣ��tag��λ�� */
extern yy_p_off_t yy_x_flv_file_first_data_tag2( yy_f_file_obj_t * f );

/* �ȵ�һ�ν�����һ����Ƶ������Ƶtag����������tag��Ѱ�ҳ��ֵĵ�һ������keyframe��tag */
extern int yy_x_flv_file_first_data_tag2_and_keyframe( yy_f_file_obj_t * f, yy_p_off_t *data_pos, yy_p_off_t *keyframe_pos);

/* ��ȡTAG��ʱ�� */
extern yy_p_uint32 yy_x_flv_tag_time( yy_x_flv_tagheader_t * tagh );

/* �Ե�һ�����ݰ���ʱ��Ϊ׼,������ʱ�䳤��,��λΪ���� */
extern yy_p_off_t yy_x_flv_file_skip_time2( yy_f_file_obj_t * f, yy_p_uint32 ms );

/* �ָ�����״̬ */
#pragma pack(pop)
#endif
