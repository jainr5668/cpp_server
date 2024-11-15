import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { ProductcardComponent } from './productcard.component';
import { TranslateModule } from "@ngx-translate/core";
import {RouterModule} from '@angular/router';
import { ImagesliderModule } from '@patterns/imageslider';

@NgModule({
  declarations: [ProductcardComponent, ],
  imports: [
    CommonModule,
    ImagesliderModule,
    TranslateModule,
    RouterModule
  ],
  exports: [ProductcardComponent],
})
export class ProductcardModule {}