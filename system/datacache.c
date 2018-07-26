#include "datacache.h"

#include "memory.h"

#include "log.h"

int32_t init_datacache( CDataCache *const pDataCache, int32_t iMaxLen )
{
	int iRetCode = -1;

	if ( pDataCache && iMaxLen > 0 )
	{
		pDataCache->locker = create_mutex();
		if ( pDataCache->locker )
		{
			pDataCache->pDataBuf = mem_malloc( iMaxLen );
			if ( pDataCache->pDataBuf )
			{
				memset( pDataCache->pDataBuf, 0x00, iMaxLen );
				pDataCache->Front = pDataCache->Rear = 0;
				pDataCache->BufLen = 0;
				pDataCache->DataBufSize = iMaxLen;
				pDataCache->iCurrDetectIndex = 0;
				
				*(pDataCache->pDataBuf + iMaxLen - 1) = 1;
			
				iRetCode = 0;
			}
			else
			{
				destory_mutex( &pDataCache->locker );
			}
		}
	}

	return iRetCode;
}

int32_t fini_datacache( CDataCache *const pDataCache )
{
	int iRetCode = -1;

	if ( pDataCache )
	{
		mem_free(pDataCache->pDataBuf);
		iRetCode = destory_mutex( &pDataCache->locker );
	}

	return iRetCode;
}

int32_t clear_datacache( CDataCache *const pDataCache )
{
	int32_t iRetCode = -1;

	pDataCache->Front = pDataCache->Rear = 0;
	pDataCache->BufLen = 0;
	pDataCache->iCurrDetectIndex = 0;

	iRetCode = 0;

	return iRetCode;
}

int32_t get_datacache_size( CDataCache *const pDataCache )
{
    int32_t iRetCode = -1;

    lock(pDataCache->locker);

    if ( pDataCache )
    {
        iRetCode = pDataCache->BufLen;
    }

    unlock(pDataCache->locker);

    return iRetCode;
}

int32_t is_datacache_full( CDataCache *const pDataCache )
{
	int32_t iRetCode = 0;

	if ( pDataCache )
		if ( ( (pDataCache->Rear + 1) % pDataCache->DataBufSize ) == pDataCache->Front )
			iRetCode = 1;

	return iRetCode;
}

int write_datacache( CDataCache *const pDataCache, const void *pData, const int iDataLen )
{
#if 1
	int iRetCode = -1;
	unsigned char *pStartBuf = NULL;

	//printf("write_datacache:-->\r\n" );
	
	if ( !pDataCache || !pData || iDataLen <= 0 )
		return iRetCode;

	lock(pDataCache->locker);

	if ( ((pDataCache->Rear + 1) % pDataCache->DataBufSize) == pDataCache->Front )
	{
		//缓存已经满
	}
	else
	{
		int iNCopy = 0;
		
		if ( (pDataCache->Front == pDataCache->Rear) )
		{
//0                                                                                       100
//|||||||||||||||||||||bottom....top||||||||||||||||||||
//0-------------------------------------------------n
//        Front
//        Rear
//
			//缓冲为空
			int iTopSpace = pDataCache->DataBufSize - pDataCache->Rear - 1, 
				iBottomSpace = pDataCache->Front;
			int iNCopyedBytes = 0;

			if ( iTopSpace > 0 )
			{
				iNCopy = 0;
				
				if ( iTopSpace > iDataLen )
					iNCopy = iDataLen;
				else
					iNCopy = iTopSpace;

				pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Rear + 1) % pDataCache->DataBufSize));
				memcpy( pStartBuf, pData, iNCopy );
				pDataCache->BufLen += iNCopy;
				pDataCache->Rear += iNCopy;//队尾进
				pDataCache->Rear %= pDataCache->DataBufSize;

				iNCopyedBytes += iNCopy;
			}

			if ( iBottomSpace > 0 && iNCopyedBytes < iDataLen )
			{
				if ( iBottomSpace > (iDataLen - iNCopyedBytes) )
					iNCopy = (iDataLen - iNCopyedBytes);
				else
					iNCopy = iBottomSpace;

				pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Rear + 1) % pDataCache->DataBufSize));
				memcpy( pStartBuf, ((unsigned char *)pData + iNCopyedBytes), iNCopy );
				pDataCache->BufLen += iNCopy;
				pDataCache->Rear += iNCopy;//队尾进
				pDataCache->Rear %= pDataCache->DataBufSize;


				iNCopyedBytes += iNCopy;
			}

#if 0
			printf( "write index: %d.\r\n", pDataCache->Rear );
			printf( "read index: %d.\r\n", pDataCache->Front );
			printf( "buffer data len: %d.\r\n", pDataCache->BufLen );
			printf( "buffer size: %d.\r\n", pDataCache->DataBufSize );
#endif
			

			iRetCode = iNCopyedBytes;
		}
		else if ( pDataCache->Rear > pDataCache->Front )
		{
			//0 													 99
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//		  Front(16)
			//		                                                  Rear(68)
			//
			

			//写位置大于读位置
			int iTopFreeSpace = pDataCache->DataBufSize - pDataCache->Rear - 1;
			int iBottomFreeSpace = pDataCache->Front;
			int iNCopyedBytes = 0;

			if ( iTopFreeSpace > 0 )
			{
				iNCopy = 0;

				if ( iTopFreeSpace > iDataLen )
					iNCopy = iDataLen;
				else
					iNCopy = iTopFreeSpace;
				
				pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Rear + 1) % pDataCache->DataBufSize));
				
				memcpy( pStartBuf, pData, iNCopy );

				pDataCache->Rear += iNCopy;
				pDataCache->Rear %= pDataCache->DataBufSize;

				iNCopyedBytes += iNCopy;
			}

			if ( iBottomFreeSpace > 0 )
			{
				int iNLeftBytes = iDataLen - iNCopyedBytes;

				if ( iNLeftBytes > 0 )
				{
					iNCopy = 0;
					
					if ( iBottomFreeSpace > iNLeftBytes )
						iNCopy = iNLeftBytes;
					else
						iNCopy = iBottomFreeSpace;

					pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Rear + 1) % pDataCache->DataBufSize));
					memcpy( pStartBuf, ((unsigned char *)pData + iNCopyedBytes), iNCopy );

					pDataCache->Rear += iNCopy;
					pDataCache->Rear %= pDataCache->DataBufSize;
	
					iNCopyedBytes += iNCopy;
				}
			}

			pDataCache->BufLen += iNCopyedBytes;

#if 0
			printf( "write index: %d.\r\n", pDataCache->Rear );
			printf( "read index: %d.\r\n", pDataCache->Front );
			printf( "buffer data len: %d.\r\n", pDataCache->BufLen );
			printf( "buffer size: %d.\r\n", pDataCache->DataBufSize );
			#endif


			iRetCode = iNCopyedBytes;
		}
		else
		{
			//0 													 99
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//		                                                   Front(86)
			//		Rear(16)
			//

			//写位置小于读位置
			int iNFreeSpace = pDataCache->Front - pDataCache->Rear - 1;

			if ( iNFreeSpace > 0 )
			{
				iNCopy = 0;
				if ( iNFreeSpace > iDataLen )
					iNCopy = iDataLen;
				else
					iNCopy = iNFreeSpace;
				
				pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Rear + 1) % pDataCache->DataBufSize));
				memcpy( pStartBuf, pData, iNCopy );
				
				pDataCache->Rear += iNCopy;
				pDataCache->Rear %= pDataCache->DataBufSize;
				
				pDataCache->BufLen += iNCopy;
#if 0
				printf( "write index: %d.\r\n", pDataCache->Rear );
				printf( "read index: %d.\r\n", pDataCache->Front );
				printf( "buffer data len: %d.\r\n", pDataCache->BufLen );
				printf( "buffer size: %d.\r\n", pDataCache->DataBufSize );
				#endif

				
				iRetCode = iNCopy;
			}
		}
	}

	//printf( "----------------------------------------->\r\n" );

#if 0//(LOG_SUPPORT)
		{
		
				char logBuf[128];
				sprintf(logBuf, "pDataCache->Front-->%d, pDataCache-->Rear-->%d, pDataCache-->BufLen-->%d, pDataCache-->DataBufSize-->%d.", 
							pDataCache->Front, pDataCache->Rear, pDataCache->BufLen, pDataCache->DataBufSize );
				LOGD(logBuf);
		}
#endif

	unlock(pDataCache->locker);

	return iRetCode;

//|||||||||||||||||||||bottom....top||||||||||||||||||||
//0-------------------------------------------------n
//Front
//           Rear
//

#else
	

#endif
}

//b                                                                                       t
//|||||||||||||||||||||bottom....top||||||||||||||||||||
//0-------------------------------------------------n
//                                            Front
//                            Rear
//
int read_datacache( CDataCache *const pDataCache, void *pOutDataBuf, const int iDataBufLen )
{
#if 1
	int iRetCode = -1;
	unsigned char *pStartBuf = NULL;

	//printf("read_datacache:-->\r\n" );
	if ( !pDataCache || !pOutDataBuf || iDataBufLen < 0 )
		return iRetCode;

	lock(pDataCache->locker);

	//printf( "----------------------------------------->\r\n" );

	if ( pDataCache->Front == pDataCache->Rear )
	{
		//缓存为空
		
	}
	else
	{
		int iNCopy = 0;
		
		//缓存有数据
		if ( pDataCache->Rear > pDataCache->Front )
		{
			//b 																					  t
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//		Front(12)
			//							  Rear(60)
			//
			

			//写位置大于读位置
			int iLeftBytes = pDataCache->Rear - pDataCache->Front;

			if ( iLeftBytes > 0 )
			{
				iNCopy = 0;
				if ( iLeftBytes > iDataBufLen )
					iNCopy = iDataBufLen;
				else
					iNCopy	= iLeftBytes;
				
				pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Front + 1) % pDataCache->DataBufSize));
				memcpy( pOutDataBuf, pStartBuf, iNCopy );
				
				pDataCache->Front += iNCopy;
				pDataCache->Front %= pDataCache->DataBufSize;
				
				pDataCache->BufLen -= iNCopy;

				pDataCache->iCurrDetectIndex = pDataCache->Front;
#if 0
				printf( "write index: %d.\r\n", pDataCache->Rear );
				printf( "read index: %d.\r\n", pDataCache->Front );
				printf( "buffer data len: %d.\r\n", pDataCache->BufLen );
				printf( "buffer size: %d.\r\n", pDataCache->DataBufSize );
#endif
				

				iRetCode = iNCopy;
			}
		}
		else
		{
			//b 												        t
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//		                                     Front(60)
			//	  Rear(12)
			//

			

			//写位置小于读位置
			int iTopLeftBytes = pDataCache->DataBufSize - pDataCache->Front - 1;
			int iBottomLeftBytes = pDataCache->Rear;
			int iNCopyedBytes = 0;

			if ( iTopLeftBytes > 0 )
			{
				if ( iTopLeftBytes > iDataBufLen )
					iNCopy = iDataBufLen;
				else
					iNCopy = iTopLeftBytes;

				pStartBuf = (pDataCache->pDataBuf + ( (pDataCache->Front + 1) % pDataCache->DataBufSize ));
				memcpy( pOutDataBuf, pStartBuf, iNCopy );
				
				pDataCache->Front += iNCopy;
				pDataCache->Front %= pDataCache->DataBufSize;

				pDataCache->BufLen -= iNCopy;

				pDataCache->iCurrDetectIndex = pDataCache->Front;

				iNCopyedBytes += iNCopy;
			}

			if ( iBottomLeftBytes > 0 )
			{
				int iNLeft = iDataBufLen - iNCopyedBytes;

				if ( iNLeft > 0 )
				{
					iNCopy = 0;
					
					if ( iBottomLeftBytes > iNLeft )
						iNCopy = iNLeft;
					else
						iNCopy = iBottomLeftBytes;

					pStartBuf = (pDataCache->pDataBuf + ( (pDataCache->Front + 1) % pDataCache->DataBufSize ) );
					memcpy( (unsigned char *)pOutDataBuf + iNCopyedBytes, pStartBuf, iNCopy );

					pDataCache->Front += iNCopy;
					pDataCache->Front %= pDataCache->DataBufSize;

					pDataCache->BufLen -= iNCopy;

					pDataCache->iCurrDetectIndex = pDataCache->Front;

					iNCopyedBytes += iNCopy;
				}
			}
#if 0
			printf( "write index: %d.\r\n", pDataCache->Rear );
			printf( "read index: %d.\r\n", pDataCache->Front );
			printf( "buffer data len: %d.\r\n", pDataCache->BufLen );
			printf( "buffer size: %d.\r\n", pDataCache->DataBufSize );
#endif

			iRetCode = iNCopyedBytes;
		}
	}

	//printf( "----------------------------------------->\r\n" );
#if 0//(LOG_SUPPORT)
	{
	
			char logBuf[128];
			sprintf(logBuf, "pDataCache->Front-->%d, pDataCache-->Rear-->%d, pDataCache-->BufLen-->%d, pDataCache-->DataBufSize-->%d.", 
						pDataCache->Front, pDataCache->Rear, pDataCache->BufLen, pDataCache->DataBufSize );
			LOGD(logBuf);
	}
#endif
		

	unlock(pDataCache->locker);

	return iRetCode;

	//b 																					  t
	//|||||||||||||||||||||bottom....top||||||||||||||||||||
	//0-------------------------------------------------n
	//											  Front
	//							  Rear
	//
	
#else

#endif
}

int snifer_datacache( CDataCache *const pDataCache, void *pOutDataBuf, const int iDataBufLen )
{
#if 1
	int iRetCode = -1;
	unsigned char *pStartBuf = NULL;

	//printf("read_datacache:-->\r\n" );
	if ( !pDataCache || !pOutDataBuf || iDataBufLen < 0 )
		return iRetCode;

	lock(pDataCache->locker);

	//printf( "----------------------------------------->\r\n" );

	if ( pDataCache->Front == pDataCache->Rear )
	{
		//缓存为空

	}
	else
	{
		int iNCopy = 0;

		//缓存有数据
		if ( pDataCache->Rear > pDataCache->Front )
		{
			//b 																					  t
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//		Front(12)
			//							  Rear(60)
			//


			//写位置大于读位置
			int iLeftBytes = pDataCache->Rear - pDataCache->Front;

			if ( iLeftBytes > 0 )
			{
				iNCopy = 0;
				if ( iLeftBytes > iDataBufLen )
					iNCopy = iDataBufLen;
				else
					iNCopy	= iLeftBytes;

				pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Front + 1) % pDataCache->DataBufSize));
				memcpy( pOutDataBuf, pStartBuf, iNCopy );

				iRetCode = iNCopy;
			}
		}
		else
		{
			//b 												        t
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//		                                     Front(60)
			//	  Rear(12)
			//



			//写位置小于读位置
			int iTopLeftBytes = pDataCache->DataBufSize - pDataCache->Front - 1;
			int iBottomLeftBytes = pDataCache->Rear;
			int iNCopyedBytes = 0;

			if ( iTopLeftBytes > 0 )
			{
				if ( iTopLeftBytes > iDataBufLen )
					iNCopy = iDataBufLen;
				else
					iNCopy = iTopLeftBytes;

				pStartBuf = (pDataCache->pDataBuf + ( (pDataCache->Front + 1) % pDataCache->DataBufSize ));
				memcpy( pOutDataBuf, pStartBuf, iNCopy );

				iNCopyedBytes += iNCopy;
			}

			if ( iBottomLeftBytes > 0 )
			{
				int iNLeft = iDataBufLen - iNCopyedBytes;

				if ( iNLeft > 0 )
				{
					iNCopy = 0;

					if ( iBottomLeftBytes > iNLeft )
						iNCopy = iNLeft;
					else
						iNCopy = iBottomLeftBytes;

					pStartBuf = (pDataCache->pDataBuf + ( (pDataCache->Front + 1) % pDataCache->DataBufSize ) );
					memcpy( (unsigned char *)pOutDataBuf + iNCopyedBytes, pStartBuf, iNCopy );

					iNCopyedBytes += iNCopy;
				}
			}

			iRetCode = iNCopyedBytes;
		}
	}

	unlock(pDataCache->locker);

	return iRetCode;

	//b 																					  t
	//|||||||||||||||||||||bottom....top||||||||||||||||||||
	//0-------------------------------------------------n
	//											  Front
	//							  Rear
	//

#else

#endif
}

//b 																					  t
//|||||||||||||||||||||bottom....top||||||||||||||||||||
//0-------------------------------------------------n
//            Front
//							  Rear
//
int search_datacache( CDataCache *const pDataCache, const unsigned char *pKeyBuf, const int iKeyBufLen )
{
#if 1
#define TEST_SUPPORT  (0)

	int iRetCode = -1;
	unsigned char *pStartBuf = NULL;


	//printf( "search_datacache:-->\r\n" );
	if ( !pDataCache || !pKeyBuf || iKeyBufLen <= 0 )
		return iRetCode;

	#if (LOG_SUPPORT)
	{
		LOGD("pDataCache-->iCurrDetectIndex-->%d, iKeyBufLen-->%d.\r\n", 
			 pDataCache->iCurrDetectIndex, iKeyBufLen);
		LOGD("0x%02x 0x%02x 0x%02x 0x%02x", pKeyBuf[0], pKeyBuf[1], pKeyBuf[2], pKeyBuf[3]);
	}
	#endif

	lock(pDataCache->locker);

	//printf( "----------------------------------------->\r\n" );

	if ( pDataCache->Front == pDataCache->Rear )
	{
		//缓存为空
		
	}
	else
	{
		int iIndex = 0;
		
		//缓存有数据
		if ( pDataCache->Rear > pDataCache->Front )
		{
			//b 																					  t
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//			  Front
			//							  Rear
			//
			

			//写位置大于读位置
			int iLeftBytes = pDataCache->Rear - pDataCache->Front;

			if ( iLeftBytes > iKeyBufLen )
			{
				int i = 0;

				iIndex = pDataCache->iCurrDetectIndex;
				iIndex %= pDataCache->DataBufSize;
				pStartBuf = (pDataCache->pDataBuf + iIndex);

				//查找
				for ( i = 1; i < iLeftBytes - iKeyBufLen; i++ )
				{
					if ( 0 == memcmp( pStartBuf + i, pKeyBuf, iKeyBufLen ) )
					{
						
						//找到关键码
						LOGD("found start key code........................");
						iRetCode = i;

						#if (LOG_SUPPORT)
						{
							LOGD("iIndex-->%d, i-->%d.", iIndex, i);
						}
						#endif

						break ;
					}

				}

				if ( iRetCode < 0 )
					pDataCache->iCurrDetectIndex += i;
				
			}
		}
		else
		{
			//b 																					  t
			//|||||||||||||||||||||bottom....top||||||||||||||||||||
			//0-------------------------------------------------n
			//			                                   Front
			//	Rear
			//
			

			//写位置小于读位置
			int iTopLeftBytes = pDataCache->DataBufSize - pDataCache->Front - 1;
			int iBottomLeftBytes = pDataCache->Rear;
			int iTotalLeftBytes = iTopLeftBytes + iBottomLeftBytes;
			int i = 0;

			iIndex = pDataCache->iCurrDetectIndex;
			iIndex %= pDataCache->DataBufSize;
			pStartBuf = (pDataCache->pDataBuf + iIndex);

			for ( i = 0 + 1; i < iTotalLeftBytes - iKeyBufLen; i++ )
			{
				if ( i < iTopLeftBytes - iKeyBufLen )
				{
					//在TOP段数据中比较
					if ( 0 == memcmp( pStartBuf + i, pKeyBuf, iKeyBufLen ) )
					{
						iRetCode = i;
					#if (LOG_SUPPORT)
					{
						LOGD("iIndex-->%d, i-->%d.", iIndex, i);
					}
					#endif

						break ;
					}

				}
				else if ( i > iTopLeftBytes )
				{
					//在BOTTOM端数据中比较
					if ( 0 == memcmp( pDataCache->pDataBuf + i - iTopLeftBytes, pKeyBuf, iKeyBufLen ) )
					{
						iRetCode = i;
					#if (LOG_SUPPORT)
					{
						LOGD("iIndex-->%d, i-->%d.", iIndex, i);
					}
					#endif

						break ;
					}
				}
				else
				{
					//TOP, BOTTOM两端中比较
					int iTopCmpLen = iKeyBufLen - (iTopLeftBytes - i);
					int iBottomCmpLen = iKeyBufLen - iTopCmpLen;

					if ( (0 == memcmp( pStartBuf + i, pKeyBuf, iTopCmpLen )) && 
							( 0 == memcmp( pDataCache->pDataBuf, pKeyBuf + iTopCmpLen, iBottomCmpLen ) ) )
					{
						iRetCode = i;
					#if (LOG_SUPPORT)
					{
						LOGD("iIndex-->%d, i-->%d.", iIndex, i);
					}
					#endif

						break ;
					}
				}
			}

			if ( iRetCode < 0 )
				pDataCache->iCurrDetectIndex += i;

#if (LOG_SUPPORT)
			if ( iRetCode > 0 )
			{
				LOGD("found h264 nal frame.");
			}
#endif
			
		}
	}

	//printf( "----------------------------------------->\r\n" );

	unlock(pDataCache->locker);

	return iRetCode;

//b 													 t
//|||||||||||||||||||||bottom....top||||||||||||||||||||
//0-------------------------------------------------n
//                                              Front
//			Rear
//

#else

#endif
}

int32_t reset_datacache( CDataCache *const pDataCache )
{
	int32_t iRetCode = -1;

	if ( pDataCache )
	{
		mem_free( pDataCache->pDataBuf );
		pDataCache->pDataBuf = NULL;

		destory_mutex( &pDataCache->locker );

		iRetCode = 0;
	}

	return iRetCode;
}

EXPORT_API void show_datacache( CDataCache *const pDataCache )
{
	LOGD("show_datacache:-->");
	if ( pDataCache )
	{
		int32_t iTempIndex = pDataCache->Front + 1;
		int8_t pInfoBuf[1024 * 100 * 5] = { 0x00, };
		char logBuf[128];
		
		iTempIndex %= pDataCache->DataBufSize;

		LOGD("pDataCache->Front-->%d, pDataCache->Rear-->%d,  pDataCache->DataBufSize-->%d.", 
			pDataCache->Front, pDataCache->Rear,  pDataCache->DataBufSize);
		while ( iTempIndex != pDataCache->Rear )
		{
			char info[32];

			sprintf(info, "0x%02x ", *(pDataCache->pDataBuf + iTempIndex) );

			iTempIndex++;

			iTempIndex %= pDataCache->DataBufSize;

			strcat( pInfoBuf, info );
			
		}

		//LOGD(pInfoBuf);
	}
	else
		LOGD("!if ( pDataCache )");

	LOGD("show_datacache end<----");
}


int32_t get_datacache_left_size( CDataCache *const pDataCache )
{
    int32_t iRetCode = -1;

    lock(pDataCache->locker);

    if ( pDataCache )
        iRetCode = pDataCache->DataBufSize - pDataCache->BufLen;

    unlock(pDataCache->locker);

    return iRetCode;
}

//b                                                                                       t
//|||||||||||||||||||||bottom....top||||||||||||||||||||
//0-------------------------------------------------n
//                                            Front
//                            Rear
//
int read_offset( CDataCache *const pDataCache, const int iDataBufLen )
{
#if 1
    int iRetCode = -1;
    unsigned char *pStartBuf = NULL;

    //printf("read_datacache:-->\r\n" );
    if ( !pDataCache || iDataBufLen < 0 )
        return iRetCode;

    lock(pDataCache->locker);

    //printf( "----------------------------------------->\r\n" );

    if ( pDataCache->Front == pDataCache->Rear )
    {
        //缓存为空

    }
    else
    {
        int iNCopy = 0;

        //缓存有数据
        if ( pDataCache->Rear > pDataCache->Front )
        {
            //b 																					  t
            //|||||||||||||||||||||bottom....top||||||||||||||||||||
            //0-------------------------------------------------n
            //		Front(12)
            //							  Rear(60)
            //


            //写位置大于读位置
            int iLeftBytes = pDataCache->Rear - pDataCache->Front;

            if ( iLeftBytes > 0 )
            {
                iNCopy = 0;
                if ( iLeftBytes > iDataBufLen )
                    iNCopy = iDataBufLen;
                else
                    iNCopy	= iLeftBytes;

                pStartBuf = (pDataCache->pDataBuf + ((pDataCache->Front + 1) % pDataCache->DataBufSize));

                pDataCache->Front += iNCopy;
                pDataCache->Front %= pDataCache->DataBufSize;

                pDataCache->BufLen -= iNCopy;

                pDataCache->iCurrDetectIndex = pDataCache->Front;
#if 0
                printf( "write index: %d.\r\n", pDataCache->Rear );
                printf( "read index: %d.\r\n", pDataCache->Front );
                printf( "buffer data len: %d.\r\n", pDataCache->BufLen );
                printf( "buffer size: %d.\r\n", pDataCache->DataBufSize );
#endif


                iRetCode = iNCopy;
            }
        }
        else
        {
            //b 												        t
            //|||||||||||||||||||||bottom....top||||||||||||||||||||
            //0-------------------------------------------------n
            //		                                     Front(60)
            //	  Rear(12)
            //



            //写位置小于读位置
            int iTopLeftBytes = pDataCache->DataBufSize - pDataCache->Front - 1;
            int iBottomLeftBytes = pDataCache->Rear;
            int iNCopyedBytes = 0;

            if ( iTopLeftBytes > 0 )
            {
                if ( iTopLeftBytes > iDataBufLen )
                    iNCopy = iDataBufLen;
                else
                    iNCopy = iTopLeftBytes;

                pStartBuf = (pDataCache->pDataBuf + ( (pDataCache->Front + 1) % pDataCache->DataBufSize ));

                pDataCache->Front += iNCopy;
                pDataCache->Front %= pDataCache->DataBufSize;

                pDataCache->BufLen -= iNCopy;

                pDataCache->iCurrDetectIndex = pDataCache->Front;

                iNCopyedBytes += iNCopy;
            }

            if ( iBottomLeftBytes > 0 )
            {
                int iNLeft = iDataBufLen - iNCopyedBytes;

                if ( iNLeft > 0 )
                {
                    iNCopy = 0;

                    if ( iBottomLeftBytes > iNLeft )
                        iNCopy = iNLeft;
                    else
                        iNCopy = iBottomLeftBytes;

                    pStartBuf = (pDataCache->pDataBuf + ( (pDataCache->Front + 1) % pDataCache->DataBufSize ) );

                    pDataCache->Front += iNCopy;
                    pDataCache->Front %= pDataCache->DataBufSize;

                    pDataCache->BufLen -= iNCopy;

                    pDataCache->iCurrDetectIndex = pDataCache->Front;

                    iNCopyedBytes += iNCopy;
                }
            }
#if 0
            printf( "write index: %d.\r\n", pDataCache->Rear );
            printf( "read index: %d.\r\n", pDataCache->Front );
            printf( "buffer data len: %d.\r\n", pDataCache->BufLen );
            printf( "buffer size: %d.\r\n", pDataCache->DataBufSize );
#endif

            iRetCode = iNCopyedBytes;
        }
    }

    //printf( "----------------------------------------->\r\n" );
#if 0//(LOG_SUPPORT)
    {

        char logBuf[128];
        sprintf(logBuf, "pDataCache->Front-->%d, pDataCache-->Rear-->%d, pDataCache-->BufLen-->%d, pDataCache-->DataBufSize-->%d.", 
            pDataCache->Front, pDataCache->Rear, pDataCache->BufLen, pDataCache->DataBufSize );
        LOGD(logBuf);
    }
#endif


    unlock(pDataCache->locker);

    return iRetCode;

    //b 																					  t
    //|||||||||||||||||||||bottom....top||||||||||||||||||||
    //0-------------------------------------------------n
    //											  Front
    //							  Rear
    //

#else

#endif
}