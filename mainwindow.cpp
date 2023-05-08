# i n c l u d e   " m a i n w i n d o w . h " 
 # i n c l u d e   " u i _ m a i n w i n d o w . h " 
 # i n c l u d e   < Q S e t t i n g s > 
 # i n c l u d e   < Q F i l e > 
 # i n c l u d e   < Q T e x t C o d e c > 
 # i n c l u d e   < Q F i l e D i a l o g > 
 
 M a i n W i n d o w : :   M a i n W i n d o w ( Q W i d g e t   * p a r e n t ) :   Q M a i n W i n d o w ( p a r e n t ) ,   u i ( n e w   U i : : M a i n W i n d o w ) { 
         u i   - >   s e t u p U i ( t h i s ) ; 
         a u t o   t o o l B a r T e m p   =   u i   - >   t o o l B a r ; 
         r e m o v e T o o l B a r ( u i   - >   t o o l B a r ) ; 
         a d d T o o l B a r ( Q t : :   B o t t o m T o o l B a r A r e a ,   t o o l B a r T e m p ) ; 
         t o o l B a r T e m p   - >   s h o w ( ) ; 
         c o n n e c t ( u i   - >   a c t i o n I m p o r t ,   & Q A c t i o n : : t o g g l e d ,   t h i s ,   & M a i n W i n d o w : :   A c t i o n I m p o r t C l i c k e d ) ; 
 
         / /   l o a d F r o m F i l e ( " C : \ \ U s e r s \ \ h o u j i \ \ D e s k t o p \ \ t e s t . t x t " ) ; 
 } 
 
 M a i n W i n d o w : :   ~ M a i n W i n d o w ( ) { 
         d e l e t e   u i ; 
 } 
 
 M a t r i x   M a i n W i n d o w : :   L o a d F r o m F i l e ( c o n s t   Q S t r i n g   & f i l e p a t h ) { 
         M a t r i x   r e t ; 
         Q F i l e   f i l e ( f i l e p a t h ) ; 
         i f   ( ! f i l e . o p e n ( Q I O D e v i c e : :   R e a d O n l y   |   Q I O D e v i c e : :   T e x t ) ) { 
                 q D e b u g ( )   < <   " �e�NSb _1Y%��" ; 
                 f i l e . c l o s e ( ) ; 
                 r e t u r n   r e t ; 
         } 
         / / Q T e x t C o d e c   * c o d e c   =   Q T e x t C o d e c : : c o d e c F o r N a m e ( " U T F - 1 6 L E " ) ; 
         Q T e x t S t r e a m   i n ( & f i l e ) ; 
         i n . s e t E n c o d i n g ( Q S t r i n g C o n v e r t e r : :   U t f 1 6 L E ) ; 
         w h i l e   ( ! i n . a t E n d ( ) ) { 
                 Q S t r i n g   l i n e   =   i n . r e a d L i n e ( ) ; 
                 / /   Q S t r i n g   l i n e   =   Q S t r i n g : : f r o m U t f 1 6 ( r e i n t e r p r e t _ c a s t < c o n s t   c h a r 1 6 _ t * > ( f i l e . r e a d L i n e ( ) . c o n s t D a t a ( ) ) ) ; 
                 i f   ( l i n e . s t a r t s W i t h ( Q S t r i n g ( " �]-N�T�vpenc( � V ) < 9 6 0 > = " ) ) ) { 
                         Q V e c t o r < d o u b l e >   & r o w   =   r e t . a d d R o w ( ) ; 
                         l i n e . r e p l a c e ( " �]-N�T�vpenc( � V ) < 9 6 0 > = " ,   " " ) ; 
                         l i n e . r e p l a c e ( " \ n " ,   " " ) ; 
                         w h i l e   ( l i n e . e n d s W i t h ( " / " )   & &   ! i n . a t E n d ( ) ) { 
                                 l i n e . r e p l a c e ( " / " ,   " , " ) ; 
                                 l i n e . a p p e n d ( i n . r e a d L i n e ( ) ) ; 
                         } 
                         l i n e . r e p l a c e ( ' , ' ,   '   ' ) ; 
                         Q T e x t S t r e a m   i n 1 ( & l i n e ) ; 
                         w h i l e   ( ! i n 1 . a t E n d ( ) ) { 
                                 d o u b l e   d ;   i n 1   > >   d ; 
                                 r o w . a p p e n d ( d ) ; 
                         } 
                         q D e b u g ( )   < <   l i n e ; 
                 } 
         } 
         f i l e . c l o s e ( ) ; 
         r e t u r n   r e t ; 
 } 
 
 v o i d   M a i n W i n d o w : :   A c t i o n I m p o r t C l i c k e d ( ) { 
         Q S t r i n g   f i l e P a t h   =   Q F i l e D i a l o g : :   g e t O p e n F i l e N a m e ( t h i s ,   Q S t r i n g ( " ��	��b�e�N" ) ,   Q S t r i n g ( ) ,   Q S t r i n g ( " �e,g�ech  * t x t " ) ) ; 
         i f   ( f i l e P a t h . i s E m p t y ( ) ) { 
                 r e t u r n ; 
         } 
         Q S t r i n g   f i l e N a m e   =   f i l e P a t h . s p l i t ( ' / ' ) . l a s t ( ) . s p l i t ( ' . ' ) . f i r s t ( ) ; 
         M a t r i x   r e t   =   L o a d F r o m F i l e ( f i l e P a t h ) ; 
         i n t   r o w C n t   =   r e t . r o w ( ) ; 
         f o r   ( i n t   i   =   0 ;   i   <   r o w C n t ;   i   + + ) { 
                 i n t   c o l C n t   =   r e t [ i ] . s i z e ( ) ;   / /   t��
N/f9 6 0 *Npenc
                 f o r   ( i n t   j   =   0 ;   j   <   c o l C n t ;   j   + + ) { 
 
                 } 
         } 
 } 
 