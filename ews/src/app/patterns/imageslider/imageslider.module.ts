import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { ImagesliderComponent } from './imageslider.component';
import { TranslateModule } from "@ngx-translate/core";
import { RouterModule } from '@angular/router';

@NgModule({
  declarations: [ImagesliderComponent, ],
  imports: [
    CommonModule,
    RouterModule,
    TranslateModule
  ],
  exports: [ImagesliderComponent],
})
export class ImagesliderModule {}