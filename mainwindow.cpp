# i n c l u d e   " m a i n w i n d o w . h " 
 # i n c l u d e   " u i _ m a i n w i n d o w . h " 
 # i n c l u d e   < Q S e t t i n g s > 
 # i n c l u d e   < Q F i l e > 
 # i n c l u d e   < Q T e x t C o d e c > 
 # i n c l u d e   < Q F i l e D i a l o g > 
 # i n c l u d e   < Q P r o g r e s s D i a l o g > 
 # i n c l u d e   < Q M e s s a g e B o x > 
 
 M a i n W i n d o w : :   M a i n W i n d o w ( Q W i d g e t   * p a r e n t ) :   Q M a i n W i n d o w ( p a r e n t ) ,   u i ( n e w   U i : : M a i n W i n d o w ) { 
         u i   - >   s e t u p U i ( t h i s ) ; 
         u i   - >   a c t i o n A n a l y s e   - >   s e t C h e c k a b l e ( f a l s e ) ; 
         u i   - >   a c t i o n I m p o r t   - >   s e t C h e c k a b l e ( f a l s e ) ; 
 
         c u r r e n t I n f o   =   n u l l p t r ; 
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
         w h i l e   ( ! i n . a t E n d ( ) ) { 
                 Q S t r i n g   l i n e   =   i n . r e a d L i n e ( ) ; 
                 / /   Q S t r i n g   l i n e   =   Q S t r i n g : : f r o m U t f 1 6 ( r e i n t e r p r e t _ c a s t < c o n s t   c h a r 1 6 _ t * > ( f i l e . r e a d L i n e ( ) . c o n s t D a t a ( ) ) ) ; 
                 i f   ( l i n e . s t a r t s W i t h ( Q S t r i n g ( " �]-N�T�vpenc( � V ) < 9 6 0 > = " ) ) ) { 
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
         c u r r e n t I n f o   =   n e w   P a t i e n t I n f o ( i n f o ) ; 
 } 
 
 
 v o i d   M a i n W i n d o w : : o n _ a c t i o n A n a l y s e _ t r i g g e r e d ( ) { 
         i f   ( c u r r e n t I n f o   = =   n u l l p t r ) { 
                 Q M e s s a g e B o x   m s g B o x ; 
                 m s g B o x . s e t T e x t ( " ��HQ�[eQ�e�N�" ) ; 
                 m s g B o x . s e t I c o n ( Q M e s s a g e B o x : :   W a r n i n g ) ; 
                 m s g B o x . e x e c ( ) ; 
                 r e t u r n ; 
         } 
         i n t   b w C n t   =   c u r r e n t I n f o   - >   G e t B r a i n W a v e ( ) . R o w n ( ) ; 
         Q P r o g r e s s D i a l o g   p r o g r e s s ( " ck(WR�g& & " ,   " -NbkR�g" ,   0 ,   b w C n t ,   t h i s ) ; 
         p r o g r e s s . s e t W i n d o w M o d a l i t y ( Q t : :   W i n d o w M o d a l ) ; 
 
         Q S e t t i n g s   s e t t i n g s ( " B r a i n W a v e " ) ; 
         i n t   w i n d o w S i z e   =   s e t t i n g s . v a l u e ( " w i n d o w S i z e " ) . t o I n t ( ) ; 
         w i n d o w S i z e   =   1 0 ; 
 
         f o r   ( i n t   i   =   0 ;   i   <   b w C n t ;   i   + + ) { 
                 p r o g r e s s . s e t V a l u e ( i ) ; 
                 i f   ( p r o g r e s s . w a s C a n c e l e d ( ) ) { 
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
                 q D e b u g ( )   < <   r e s ; 
                 b r e a k ; 
         } 
         p r o g r e s s . s e t V a l u e ( b w C n t ) ; 
         Q M e s s a g e B o x   m s g B o x ; 
         m s g B o x . s e t T e x t ( " R�g�[�k��~�g�]�OX[�e�N" ) ; 
         m s g B o x . e x e c ( ) ; 
 } 
 
 