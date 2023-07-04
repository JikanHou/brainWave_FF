# i n c l u d e   " m a i n w i n d o w . h " 
 # i n c l u d e   " u i _ m a i n w i n d o w . h " 
 # i n c l u d e   < Q S e t t i n g s > 
 # i n c l u d e   < Q F i l e > 
 # i n c l u d e   < Q T e x t C o d e c > 
 # i n c l u d e   < Q F i l e D i a l o g > 
 # i n c l u d e   < Q P r o g r e s s D i a l o g > 
 # i n c l u d e   < Q M e s s a g e B o x > 
 # i n c l u d e   < w i n d o w s . h > 
 # i n c l u d e   " q c u s t o m p l o t . h " 
 
 M a i n W i n d o w : :   M a i n W i n d o w ( Q W i d g e t   * p a r e n t ) :   Q M a i n W i n d o w ( p a r e n t ) ,   u i ( n e w   U i : : M a i n W i n d o w ) { 
         u i   - >   s e t u p U i ( t h i s ) ; 
         u i   - >   a c t i o n A n a l y s e   - >   s e t C h e c k a b l e ( f a l s e ) ; 
         u i   - >   a c t i o n I m p o r t   - >   s e t C h e c k a b l e ( f a l s e ) ; 
 
         c u r r e n t I n f o   =   n u l l p t r ; 
 
         / /   c o n n e c t ( u i   - >   a c t i o n I m p o r t ,   & Q A c t i o n : : t r i g g e r e d ,   t h i s ,   & M a i n W i n d o w : :   A c t i o n I m p o r t C l i c k e d ) ; 
         / /   l o a d F r o m F i l e ( " C : \ \ U s e r s \ \ h o u j i \ \ D e s k t o p \ \ t e s t . t x t " ) ; 
 } 
 
 M a i n W i n d o w : :   ~ M a i n W i n d o w ( ) { 
         d e l e t e   u i ; 
         i f   ( c u r r e n t I n f o   ! =   n u l l p t r ) { 
                 d e l e t e   c u r r e n t I n f o ; 
         } 
 } 
 
 P a t i e n t I n f o   M a i n W i n d o w : :   L o a d F r o m F i l e ( c o n s t   Q S t r i n g   & f i l e p a t h ) { 
         P a t i e n t I n f o   r e t ; 
         M a t r i x   m a t ; 
         Q F i l e   f i l e ( f i l e p a t h ) ; 
         i f   ( ! f i l e . o p e n ( Q I O D e v i c e : :   R e a d O n l y   |   Q I O D e v i c e : :   T e x t ) ) { 
                 q D e b u g ( )   < <   " �e�NSb _1Y%��" ; 
                 f i l e . c l o s e ( ) ; 
                 r e t u r n   r e t ; 
         } 
         / / Q T e x t C o d e c   * c o d e c   =   Q T e x t C o d e c : : c o d e c F o r N a m e ( " U T F - 1 6 L E " ) ; 
         Q T e x t S t r e a m   i n ( & f i l e ) ; 
         i n . s e t E n c o d i n g ( Q S t r i n g C o n v e r t e r : :   U t f 1 6 L E ) ; 
         b o o l   s   =   t r u e ; 
         w h i l e   ( ! i n . a t E n d ( ) ) { 
                 Q S t r i n g   l i n e   =   i n . r e a d L i n e ( ) ; 
                 / /   Q S t r i n g   l i n e   =   Q S t r i n g : : f r o m U t f 1 6 ( r e i n t e r p r e t _ c a s t < c o n s t   c h a r 1 6 _ t * > ( f i l e . r e a d L i n e ( ) . c o n s t D a t a ( ) ) ) ; 
                 i f   ( l i n e . s t a r t s W i t h ( Q S t r i n g ( " �]-N�T�vpenc( � V ) < 9 6 0 > = " ) ) ) { 
                         i f   ( s ) { 
                                 s   =   f a l s e ; 
                         } 
                         e l s e { 
                                 s   =   t r u e ; 
                                 c o n t i n u e ; 
                         } 
                         Q V e c t o r < d o u b l e >   r o w ; 
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
                         m a t . P u s h B a c k ( r o w ) ; 
                 } 
                 e l s e   i f   ( l i n e . s t a r t s W i t h ( Q S t r i n g ( " �Yl" ) ) ) { 
                         r e t . S e t N a m e ( l i n e . m i d ( 3 ) ) ; 
                 } 
                 e l s e   i f   ( l i n e . s t a r t s W i t h ( Q S t r i n g ( " 1\ʋ�eg" ) ) ) { 
                         r e t . S e t D a t e ( l i n e . m i d ( 5 ) ) ; 
                 } 
                 e l s e   i f   ( l i n e . s t a r t s W i t h ( Q S t r i n g ( " �`�hƋ" ) ) ) { 
                         r e t . S e t I D ( l i n e . m i d ( 5 ) ) ; 
                 } 
         } 
         f i l e . c l o s e ( ) ; 
         r e t . S e t B r a i n W a v e ( m a t ) ; 
         r e t u r n   r e t ; 
 } 
 
 v o i d   M a i n W i n d o w : :   S h o w I n f o ( c o n s t   P a t i e n t I n f o   & i n f o ) { 
         u i   - >   e d i t _ n a m e   - >   s e t T e x t ( i n f o . G e t N a m e ( ) ) ; 
         u i   - >   e d i t _ i d   - >   s e t T e x t ( i n f o . G e t I D ( ) ) ; 
         u i   - >   e d i t _ c n t   - >   s e t T e x t ( Q S t r i n g : : n u m b e r ( i n f o . G e t B r a i n W a v e ( ) . R o w n ( ) ) ) ; 
         u i   - >   e d i t _ d a t e   - >   s e t T e x t ( i n f o . G e t D a t e ( ) ) ; 
 } 
 
 
 v o i d   M a i n W i n d o w : : o n _ a c t i o n I m p o r t _ t r i g g e r e d ( ) { 
         Q S t r i n g   f i l e P a t h   =   Q F i l e D i a l o g : :   g e t O p e n F i l e N a m e ( t h i s ,   Q S t r i n g ( " ��	��b�e�N" ) ,   Q S t r i n g ( ) ,   Q S t r i n g ( " �e,g�ech  * t x t " ) ) ; 
         i f   ( f i l e P a t h . i s E m p t y ( ) ) { 
                 r e t u r n ; 
         } 
         Q S t r i n g   f i l e N a m e   =   f i l e P a t h . s p l i t ( ' / ' ) . l a s t ( ) . s p l i t ( ' . ' ) . f i r s t ( ) ; 
         P a t i e n t I n f o   i n f o   =   L o a d F r o m F i l e ( f i l e P a t h ) ; 
         S h o w I n f o ( i n f o ) ; 
         i f   ( c u r r e n t I n f o   ! =   n u l l p t r ) { 
                 d e l e t e   c u r r e n t I n f o ; 
         } 
         c u r r e n t I n f o   =   n e w   P a t i e n t I n f o ( i n f o ) ; 
 } 
 
 
 v o i d   M a i n W i n d o w : : o n _ a c t i o n A n a l y s e _ t r i g g e r e d ( ) { 
         i f   ( c u r r e n t I n f o   = =   n u l l p t r ) { 
                 Q M e s s a g e B o x   m s g B o x ; 
                 m s g B o x . s e t T e x t ( " ��HQ�[eQ�e�N�" ) ; 
                 m s g B o x . s e t W i n d o w T i t l e ( " �[eQ1Y%�" ) ; 
                 m s g B o x . s e t W i n d o w I c o n ( Q I c o n ( " : / I c o n s / f a v i c o n . i c o " ) ) ; 
                 m s g B o x . s e t I c o n ( Q M e s s a g e B o x : :   W a r n i n g ) ; 
                 m s g B o x . e x e c ( ) ; 
                 r e t u r n ; 
         } 
         i n t   b w C n t   =   c u r r e n t I n f o   - >   G e t B r a i n W a v e ( ) . R o w n ( ) ; 
         Q P r o g r e s s D i a l o g   p r o g r e s s ( " ck(WR�g& & " ,   " -NbkR�g" ,   0 ,   b w C n t ,   t h i s ) ; 
         p r o g r e s s . s e t W i n d o w T i t l e ( " �5u�lR�g" ) ; 
         p r o g r e s s . s e t W i n d o w M o d a l i t y ( Q t : :   W i n d o w M o d a l ) ; 
         p r o g r e s s . s e t M i n i m u m D u r a t i o n ( 2 0 0 0 ) ; 
         / / p r o g r e s s . e x e c ( ) ; 
 
         Q S e t t i n g s   s e t t i n g s ( " B r a i n W a v e " ) ; 
         i n t   w i n d o w S i z e   =   s e t t i n g s . v a l u e ( " w i n d o w S i z e " ,   1 0 ) . t o I n t ( ) ; 
         / / w i n d o w S i z e   =   1 0 ; 
         b o o l   c a n c e l l e d   =   f a l s e ; 
         f o r   ( i n t   i   =   0 ;   i   <   b w C n t ;   i   + + ) { 
                 p r o g r e s s . s e t V a l u e ( i ) ; 
                 i f   ( p r o g r e s s . w a s C a n c e l e d ( ) ) { 
                         c a n c e l l e d   =   t r u e ; 
                         b r e a k ; 
                 } 
                 / /   R�g�k N*N�e�N
                 Q V e c t o r < d o u b l e >   b w   =   c u r r e n t I n f o   - >   G e t R o w ( i ) ; 
                 i n t   l e n g t h   =   b w . l e n g t h ( ) ; 
                 d o u b l e   s u m   =   0 ; 
                 Q V e c t o r < d o u b l e >   w i n d o w ,   r e s ; 
                 f o r   ( i n t   i   =   0 ;   i   <   w i n d o w S i z e   & &   i   <   l e n g t h ;   i   + + ) { 
                         w i n d o w . a p p e n d ( b w [ i ] ) ; 
                         s u m   + =   b w [ i ] ; 
                 } 
                 r e s . a p p e n d ( s u m   /   w i n d o w . s i z e ( ) ) ; 
                 f o r   ( i n t   i   =   w i n d o w S i z e ;   i   <   l e n g t h ;   i   + + ) { 
                         s u m   - =   w i n d o w . f r o n t ( ) ; 
                         w i n d o w . p o p _ f r o n t ( ) ; 
                         w i n d o w . a p p e n d ( b w [ i ] ) ; 
                         s u m   + =   b w [ i ] ; 
                         r e s . a p p e n d ( s u m   /   w i n d o w . s i z e ( ) ) ; 
                 } 
                 / / q D e b u g ( )   < <   r e s ; 
                 Q S t r i n g   f i l e n a m e   =   c u r r e n t I n f o   - >   G e t N a m e ( ) ; 
                 Q S t r i n g   f i l e D a t e   =   c u r r e n t I n f o   - >   G e t D a t e ( ) ; 
                 f i l e D a t e . r e p l a c e ( " / " ,   " _ " ) . r e p l a c e ( " : " ,   " _ " ) ; 
                 f i l e n a m e   + =   f i l e D a t e   +   Q S t r i n g ( " _ " )   +   Q S t r i n g : : n u m b e r ( i   +   1 ) ; 
                 A n a l y s e B w ( f i l e n a m e   +   " . p n g " ,   r e s ) ; 
         } 
         p r o g r e s s . s e t V a l u e ( b w C n t ) ; 
         i f   ( ! c a n c e l l e d ) { 
                 Q M e s s a g e B o x   m s g B o x ; 
                 m s g B o x . s e t W i n d o w T i t l e ( " R�g�[b" ) ; 
                 m s g B o x . s e t W i n d o w I c o n ( Q I c o n ( " : / I c o n s / f a v i c o n . i c o " ) ) ; 
                 m s g B o x . s e t T e x t ( " R�g�[�k��~�g�]�OX[�e�N" ) ; 
                 m s g B o x . e x e c ( ) ; 
         } 
 } 
 
 v o i d   M a i n W i n d o w : :   A n a l y s e B w ( Q S t r i n g   f i l e n a m e ,   Q V e c t o r < d o u b l e >   b w ) { 
         Q C u s t o m P l o t   * p l o t   =   n e w   Q C u s t o m P l o t ( t h i s ) ; 
         Q V e c t o r < d o u b l e >   x ,   y   =   b w ; 
         d o u b l e   y M a x   =   - 1 0 0 0 0 ,   y M i n   =   1 0 0 0 0 0 ; 
         i n t   m a x X   =   0 ,   m i n X   =   0 ; 
         f o r   ( i n t   i   =   0 ;   i   <   y . s i z e ( ) ;   i   + + ) { 
                 x . a p p e n d ( i ) ; 
                 i f   ( y [ i ]   <   y [ m i n X ] ) { 
                         m i n X   =   i ; 
                 } 
                 i f   ( y [ i ]   >   y [ m a x X ] ) { 
                         m a x X   =   i ; 
                 } 
         } 
         Q P e n   f u n c P e n ; 
         f u n c P e n . s e t C o l o r ( Q t : :   b l a c k ) ; 
         Q C P G r a p h   * f u n c G r a p h   =   p l o t   - >   a d d G r a p h ( ) ; 
         f u n c G r a p h   - >   s e t P e n ( f u n c P e n ) ; 
         f u n c G r a p h   - >   s e t D a t a ( x ,   y ) ; 
         f u n c G r a p h   - >   s e t N a m e ( " �5u�V" ) ; 
 
         y M a x   =   y [ m a x X ] ; 
         y M i n   =   y [ m i n X ] ; 
         y M a x   =   s t d : :   c e i l ( y M a x )   +   1 ; 
         y M i n   =   s t d : :   f l o o r ( y M i n )   -   1 ; 
 
         Q C P I t e m T r a c e r   * m a x P o i n t   =   n e w   Q C P I t e m T r a c e r ( p l o t ) ; 
         Q C P I t e m T r a c e r   * m i n P o i n t   =   n e w   Q C P I t e m T r a c e r ( p l o t ) ; 
         m a x P o i n t   - >   s e t G r a p h ( f u n c G r a p h ) ; 
         m i n P o i n t   - >   s e t G r a p h ( f u n c G r a p h ) ; 
         m a x P o i n t   - >   s e t G r a p h K e y ( m a x X ) ; 
         m i n P o i n t   - >   s e t G r a p h K e y ( m i n X ) ; 
         m a x P o i n t   - >   s e t S t y l e ( Q C P I t e m T r a c e r : : t s C i r c l e ) ; 
         m a x P o i n t   - >   s e t P e n ( Q P e n ( Q t : : r e d ) ) ; 
         m a x P o i n t   - >   s e t B r u s h ( Q t : : r e d ) ; 
         m a x P o i n t   - >   s e t S i z e ( 1 5 ) ; 
         m i n P o i n t   - >   s e t S t y l e ( Q C P I t e m T r a c e r : : t s C i r c l e ) ; 
         m i n P o i n t   - >   s e t P e n ( Q P e n ( Q t : : r e d ) ) ; 
         m i n P o i n t   - >   s e t B r u s h ( Q t : : r e d ) ; 
         m i n P o i n t   - >   s e t S i z e ( 1 5 ) ; 
 
         Q C P I t e m S t r a i g h t L i n e   * m i n L i n e   =   n e w   Q C P I t e m S t r a i g h t L i n e ( p l o t ) ; 
         Q C P I t e m S t r a i g h t L i n e   * m a x L i n e   =   n e w   Q C P I t e m S t r a i g h t L i n e ( p l o t ) ; 
         m i n L i n e   - >   s e t P e n ( Q P e n ( Q t : : r e d ,   3 ,   Q t : :   D o t L i n e ) ) ; 
         m a x L i n e   - >   s e t P e n ( Q P e n ( Q t : : r e d ,   3 ,   Q t : :   D o t L i n e ) ) ; 
         m i n L i n e   - >   p o i n t 1   - >   s e t C o o r d s ( m i n X ,   - 1 0 ) ; 
         m i n L i n e   - >   p o i n t 2   - >   s e t C o o r d s ( m i n X ,   - 3 0 ) ; 
         m a x L i n e   - >   p o i n t 1   - >   s e t C o o r d s ( m a x X ,   - 1 0 ) ; 
         m a x L i n e   - >   p o i n t 2   - >   s e t C o o r d s ( m a x X ,   - 3 0 ) ; 
 
         Q C P I t e m T e x t   * m i n P o i n t T e x t   =   n e w   Q C P I t e m T e x t ( p l o t ) ; 
         m i n P o i n t T e x t   - >   s e t P o s i t i o n A l i g n m e n t ( Q t : : A l i g n L e f t   |   Q t : : A l i g n V C e n t e r ) ; 
         m i n P o i n t T e x t   - >   s e t T e x t ( Q S t r i n g ( " ( % 1 ,   % 2 ) " ) . a r g ( m i n X ) . a r g ( r o u n d ( y [ m i n X ]   *   1 0 0 )   /   1 0 0 . 0 ) ) ; 
         m i n P o i n t T e x t   - >   p o s i t i o n   - >   s e t C o o r d s ( m i n X   +   1 0 ,   y [ m i n X ] ) ; 
         m i n P o i n t T e x t   - >   s e t F o n t ( Q F o n t ( f o n t ( ) . f a m i l y ( ) ,   3 0 ) ) ; 
 
         Q C P I t e m T e x t   * m a x P o i n t T e x t   =   n e w   Q C P I t e m T e x t ( p l o t ) ; 
         m a x P o i n t T e x t   - >   s e t P o s i t i o n A l i g n m e n t ( Q t : : A l i g n L e f t   |   Q t : : A l i g n V C e n t e r ) ; 
         m a x P o i n t T e x t   - >   s e t T e x t ( Q S t r i n g ( " ( % 1 ,   % 2 ) " ) . a r g ( m a x X ) . a r g ( r o u n d ( y [ m a x X ]   *   1 0 0 )   /   1 0 0 . 0 ) ) ; 
         m a x P o i n t T e x t   - >   p o s i t i o n   - >   s e t C o o r d s ( m a x X   +   1 0 ,   y [ m a x X ] ) ; 
         m a x P o i n t T e x t   - >   s e t F o n t ( Q F o n t ( f o n t ( ) . f a m i l y ( ) ,   3 0 ) ) ; 
 
         p l o t   - >   x A x i s   - >   s e t R a n g e ( 0 ,   x . s i z e ( )   +   5 0 ) ; 
         p l o t   - >   y A x i s   - >   s e t R a n g e ( y M i n ,   y M a x ) ; 
         p l o t   - >   x A x i s   - >   s e t L a b e l ( " �e��" ) ; 
         p l o t   - >   x A x i s   - >   s e t L a b e l F o n t ( Q F o n t ( f o n t ( ) . f a m i l y ( ) ,   2 0 ) ) ; 
         p l o t   - >   y A x i s   - >   s e t L a b e l ( " 5uMO" ) ; 
         p l o t   - >   y A x i s   - >   s e t R a n g e R e v e r s e d ( t r u e ) ; 
         p l o t   - >   y A x i s   - >   s e t L a b e l F o n t ( Q F o n t ( f o n t ( ) . f a m i l y ( ) ,   2 0 ) ) ; 
 
         s t d : :   s o r t ( y . b e g i n ( ) ,   y . e n d ( ) ) ; 
         d o u b l e   s u m   =   0 ; 
         f o r   ( i n t   i   =   y . s i z e ( )   /   3 ;   i   < =   y . s i z e ( )   *   2   /   3 ;   i   + + ) { 
                 s u m   + =   y [ i ] ; 
         } 
         s u m   / =   y . s i z e ( )   *   2   /   3   -   y . s i z e ( )   /   3   +   1 ; 
 
         Q P e n   d o t P e n ; 
         d o t P e n . s e t S t y l e ( Q t : :   P e n S t y l e : :   D a s h L i n e ) ; 
         d o t P e n . s e t C o l o r ( Q t : :   b l u e ) ; 
         Q C P G r a p h   * l i n e G r a p h   =   p l o t   - >   a d d G r a p h ( ) ; 
         l i n e G r a p h   - >   s e t P e n ( d o t P e n ) ; 
 
         Q V e c t o r < d o u b l e >   y 2 ; 
         f o r   ( i n t   i   =   0 ;   i   <   y . s i z e ( ) ;   i   + + ) { 
                 y 2 . a p p e n d ( s u m ) ; 
         } 
 
         l i n e G r a p h   - >   s e t D a t a ( x ,   y 2 ) ; 
         l i n e G r a p h   - >   s e t N a m e ( Q S t r i n g ( " �W�~�% 1 " ) . a r g ( Q S t r i n g : :   n u m b e r ( s u m ) ) ) ; 
         p l o t   - >   l e g e n d   - >   s e t V i s i b l e ( t r u e ) ; 
 
 
         Q S e t t i n g s   s e t t i n g s ( " B r a i n W a v e " ) ; 
         i n t   w i d t h   =   s e t t i n g s . v a l u e ( " p i c W i d t h " ,   2 0 0 0 ) . t o I n t ( ) ; 
         i n t   h e i g h t   =   s e t t i n g s . v a l u e ( " p i c H e i g h t " ,   1 2 0 0 ) . t o I n t ( ) ; 
         q D e b u g ( )   < <   p l o t   - >   s a v e J p g ( f i l e n a m e ,   w i d t h ,   h e i g h t ) ; 
 } 
 
 v o i d   M a i n W i n d o w : : o n _ a c t i o n S e t t i n g s _ t r i g g e r e d ( ) { 
         S e t t i n g s W i n d o w   * s e t t i n g s W i n d o w   =   n e w   S e t t i n g s W i n d o w ; 
         s e t t i n g s W i n d o w   - >   s e t W i n d o w M o d a l i t y ( Q t : :   W i n d o w M o d a l ) ; 
         s e t t i n g s W i n d o w   - >   s h o w ( ) ; 
 } 
 
 