import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { TranslateModule } from '@ngx-translate/core';
import { ContentModule } from '@patterns/content';
import { FooterModule } from '@patterns/footer';
import { CardComponent } from './card.component';
@NgModule({
  declarations: [CardComponent],
  imports: [
    CommonModule,
    FooterModule,
    ContentModule,
    TranslateModule
  ],
  exports: [CardComponent],
})
export class CardModule {}