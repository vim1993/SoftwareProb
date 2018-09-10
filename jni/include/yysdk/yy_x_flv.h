#ifndef YY_X_FLV_H
#define YY_X_FLV_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
#include "yy_f_alloc.h"
#include "yy_f_buffer.h"
#include "yy_e_http.h"
#include "yy_f_file_obj.h"

/* 关于FLV文件分析 */

/* 指把原来对齐方式设置压栈，并设新的对齐方式设置为一个字节对齐 */
#pragma pack(push,1)

/* 描述文件头信息 */
typedef struct yy_x_flv_fileheader_s
{
	yy_p_uint8 signature[3];	    /* FLV */
	yy_p_uint8 version;	            //版本号 0x01-now
	yy_p_uint8 flag_video:1;	    //视频标志
	yy_p_uint8 flag_b1:1;		    //保留
	yy_p_uint8 flag_audio:1;	    //音频标志
	yy_p_uint8 flag_b5:5;		    //保留	
	yy_p_uint32 data_offset;	    //The DataOffset field usually has a value of 9 for FLV version 1. This field is present to accommodate larger headers in future versions.
}yy_x_flv_fileheader_t;
typedef struct yy_x_flv_tagheader_s
{	
	yy_p_uint32 pre_tag_size;	    //前一个tag的长度,如果第一个tag就是0
	yy_p_uint8 type;			    //* 8 -- 音频tag * 9 -- 视频tag * 18 -- 脚本tag
	yy_p_uint8 data_size[3];	    //数据区长度 3bytes 
	yy_p_uint8 timestamp[3];		//时间戳 3bytes 单位毫秒
	yy_p_uint8 timestamp_extended;	//扩展时间戳 1byte 作为时间戳的高位
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

/* 如果文件头是0x08的soundFormat = 10，就会多出一个字节，是音频解码信息 */
/* audio_tag_data结构体,位于tag_header后面 */
typedef struct yy_x_flv_tag_audiodata_h_s
{
	yy_p_uint8 sound_type:1;			/* 音频类型，0 = mono，1 = stereo */		
	yy_p_uint8 sound_size:1;			/* 采样精度，0 = 8bits，1 = 16bits */		
	yy_p_uint8 sound_rate:2;			/* 第5-6位的数值表示采样率，0 = 5.5 kHz，1 = 11 kHz，2 = 22 kHz，3 = 44 kHz */	
	yy_p_uint8 sound_format:4;			/* 音频数据格式 */
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

/* video_tag_data结构体,位于tag_header后面，如果Codec_ID = 7,则多出4个字节，包含关键帧的信息 */
typedef struct yy_x_flv_tag_videodata_h_s
{
	yy_p_uint8 codec_id:4;				/* 视频编码ID */
	yy_p_uint8 frame_type:4;			/* 帧类型 */ 	
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

/* 关键帧结构体 */
typedef struct yy_x_flv_tag_avcvideopacket_s{
    yy_p_uint8 avc_packet_type;			/* 关键帧标志 */
    yy_p_uint8 composition_time[3];		
}yy_x_flv_tag_avcvideopacket_t;

/* 查看data数据中是否存在关键帧的信息 */
extern int yy_x_flv_is_h264_keyframe( const char * data, size_t len );

/* 查看data数据中是否存在sps、pps信息，这两个信息是解码器所需的信息 */
extern int yy_x_flv_is_h264_spspps( const char * data, size_t len );

/* 查看data数据中是否存在解码音频的信息 */
extern int yy_x_flv_is_audio_meta( const char * data, size_t len );

/* 获取tag_header结构体中的tag_size字段+tag_header结构体大小,即tag_size */
extern yy_p_uint32 yy_x_flv_tag_size( yy_x_flv_tagheader_t * tagh );

/* 重新设置tag_header结构体中data_size字段，即后面data数据的长度 */
extern void yy_x_flv_set_data_size( yy_x_flv_tagheader_t * tagh, yy_p_uint32 data_size );

/* 重新设置tag_header结构体中timestamp字段和timestamp_extended字段，即后面时间戳和扩展时间戳  */
extern void yy_x_flv_set_data_timestamp( yy_x_flv_tagheader_t * tagh, yy_p_uint32 timestamp );

/* 读取文件到buf，解析buf，将解析的数据写入到buffer中,针对FLV文件，读取FLV头，如果是264文件，同时读取264 SPSPPS */
extern int yy_x_flv_file_get_metahead( yy_p_handle_t fd, yy_f_buffer_t * meta );

/* 读取文件到buf，解析buf，将解析的数据写入到buffer中,针对FLV文件，读取FLV头，如果是264文件，同时读取264 SPSPPS */
extern int yy_x_flv_file_get_metahead2(char * file_cache, yy_p_off_t file_pos, yy_f_buffer_t * meta);

/* 获取读取的flv文件的有效数据长度 */
extern int yy_x_flv_file_parse_meta_len( yy_p_handle_t fd );

/*查找第一个H264的关键帧*/
extern yy_p_off_t yy_x_flv_file_find_keyframe( yy_p_handle_t fd );

/* 获取第一次出现frame_type的tag的位置 */
extern yy_p_off_t yy_x_flv_file_find_keyframe2( yy_f_file_obj_t * f );

/* 从指定的pos位置开始获取第一次出现frame_type的tag的位置 */
extern yy_p_off_t yy_x_flv_file_find_keyframe2_by_pos( yy_f_file_obj_t * f, yy_p_off_t pos );

/*跳过flvheader,onmetadata,h264sps后第一个有效数据包的位置*/
extern yy_p_off_t yy_x_flv_file_first_data_tag( yy_p_handle_t fd );

/* 获取第一次出现视频或者音频解码信息的tag的位置 */
extern yy_p_off_t yy_x_flv_file_first_data_tag2( yy_f_file_obj_t * f );

/* 先第一次解析到一个视频或者音频tag，在跳过这tag，寻找出现的第一个包含keyframe的tag */
extern int yy_x_flv_file_first_data_tag2_and_keyframe( yy_f_file_obj_t * f, yy_p_off_t *data_pos, yy_p_off_t *keyframe_pos);

/* 读取TAG的时间 */
extern yy_p_uint32 yy_x_flv_tag_time( yy_x_flv_tagheader_t * tagh );

/* 以第一个数据包的时间为准,跳过的时间长度,单位为毫秒 */
extern yy_p_off_t yy_x_flv_file_skip_time2( yy_f_file_obj_t * f, yy_p_uint32 ms );

/* 恢复对齐状态 */
#pragma pack(pop)
#endif
